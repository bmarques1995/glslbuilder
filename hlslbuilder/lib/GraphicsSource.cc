#include "GraphicsSource.hh"
#include "GraphicsSource.hh"
#include "GraphicsSource.hh"
#include "GraphicsSource.hh"
#include "Utils/FileHandler.hh"
#include <filesystem>
#include "SolutionParser.hh"

const std::unordered_map<HLSLBuilder::ShaderStage, std::string_view> HLSLBuilder::GraphicsSource::s_FileEndpointMapper =
{
	{ ShaderStage::Vertex, "VertexFile" },
	{ ShaderStage::Pixel, "PixelFile" }
};

HLSLBuilder::GraphicsSource::GraphicsSource(std::string_view path) :
	m_Callback([](std::string value) {})
{
	FileHandler::ReadTextFile(path, &m_SourceCode);
	std::filesystem::path pathName(path.data());
	m_BaseName = pathName.stem().string();
	m_Properties["BaseName"] = m_BaseName;
	m_ParentPath = pathName.parent_path().string();
	std::replace(m_ParentPath.begin(), m_ParentPath.end(), '\\', '/');
}

void HLSLBuilder::GraphicsSource::CompileShaders(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion)
{
	if (HLSLVersion.Major < 6)
		CompileD3DCGroup(buildMode, HLSLVersion);
	else
		CompileDXCGroup(buildMode, outputTarget, HLSLVersion, VulkanVersion);
}

void HLSLBuilder::GraphicsSource::CompileD3DCGroup(BuildMode buildMode, Version HLSLVersion)
{
	D3DCBuildShader(buildMode, ShaderStage::Vertex, HLSLVersion);
	D3DCBuildShader(buildMode, ShaderStage::Pixel, HLSLVersion);
}

void HLSLBuilder::GraphicsSource::CompileDXCGroup(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion)
{
	DXCBuildShader(buildMode, outputTarget, VulkanVersion, ShaderStage::Vertex, HLSLVersion);
	DXCBuildShader(buildMode, outputTarget, VulkanVersion, ShaderStage::Pixel, HLSLVersion);
}

void HLSLBuilder::GraphicsSource::D3DCBuildShader(BuildMode buildMode, ShaderStage shaderStage, Version hlslVersion)
{
	ComPtr<ID3DBlob> errorBlob;
	ComPtr<IDxcBlob> resultBlob;
	bool present = false;
	std::stringstream treated_arg;
	std::string target = treated_arg.str();
	treated_arg.str("");
	Json::Value solution = *SolutionParser::GetSolution();

	std::string constMapResolver;
	auto it = s_EntrypointMapper.find(shaderStage);
	if (it != s_EntrypointMapper.end())
		constMapResolver = solution["GraphicsPipeline"][it->second.data()].asString();

	std::string shaderTarget = BuildShaderStageName(shaderStage, hlslVersion);
	

	uint32_t compileFlags = buildMode == BuildMode::DEBUG ? D3DCOMPILE_DEBUG : D3DCOMPILE_OPTIMIZATION_LEVEL3;

	D3DCompile(m_SourceCode.c_str(), m_SourceCode.size(), nullptr, nullptr, nullptr,
		constMapResolver.c_str(), shaderTarget.c_str(), compileFlags, 0, reinterpret_cast<ID3DBlob**>(resultBlob.GetAddressOf()), errorBlob.GetAddressOf());
	if (errorBlob != nullptr)
	{
		if (errorBlob->GetBufferSize())
		{
			std::string error = reinterpret_cast<const char*>(errorBlob->GetBufferPointer());
			throw CompileErrorException(error);
		}
	}
	else
	{
		BuildMessage(shaderStage);
		present = true;
		m_Blobs[shaderStage] = resultBlob;
		
		std::string fileOut = BuildBlobRelativePath(shaderStage, OutputTarget::CSO);
		FileHandler::WriteBinFile(fileOut.c_str(), reinterpret_cast<std::byte*>(resultBlob->GetBufferPointer()), resultBlob->GetBufferSize());
		//Console::Log("{0} successfully compiled", fileOut.str());
	}
	ValidateStage(shaderStage, present);
}

void HLSLBuilder::GraphicsSource::DXCBuildShader(BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion)
{
	ComPtr<IDxcUtils> dxc_utils = { 0 };
	ComPtr<IDxcCompiler3> dxcompiler = { 0 };
	ComPtr<IDxcBlob> resultBlob;

	bool present = false;

	DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(dxc_utils.ReleaseAndGetAddressOf()));
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(dxcompiler.GetAddressOf()));

	DxcBuffer srcBuffer;
	srcBuffer.Ptr = &(*m_SourceCode.begin());
	srcBuffer.Size = m_SourceCode.size();
	srcBuffer.Encoding = 0;

	std::wstringstream treated_arg;
	std::vector<std::wstring> args;

	PushDxcArgList(&args, buildMode, outputTarget, VulkanVersion, shaderStage, hlslVersion);

	std::vector<LPCWSTR> rawArgs;
	for (auto& i : args)
	{
		rawArgs.push_back(i.c_str());
	}

	ComPtr<IDxcResult> result;
	dxcompiler->Compile(&srcBuffer, rawArgs.data(), static_cast<uint32_t>(rawArgs.size()), nullptr, IID_PPV_ARGS(result.GetAddressOf()));

	result->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(resultBlob.GetAddressOf()), nullptr);

	ComPtr<IDxcBlobEncoding> errorBlob;
	result->GetErrorBuffer(errorBlob.GetAddressOf());

	if (errorBlob->GetBufferSize() > 0)
	{
		std::string error = reinterpret_cast<const char*>(errorBlob->GetBufferPointer());
		throw CompileErrorException(error);
	}
	else
	{
		m_Blobs[shaderStage] = resultBlob;
		present = true;
		RegisterBlob(shaderStage, outputTarget);	
	}
	ValidateStage(shaderStage, present);
}

void HLSLBuilder::GraphicsSource::PushDxcArgList(std::vector<std::wstring>* argList, BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion)
{
	std::string castingValue;
	std::wstring result;
	argList->push_back(L"-Zpc");
	argList->push_back(L"-HV");
	argList->push_back(L"2021");
	argList->push_back(L"-T");
	castingValue = BuildShaderStageName(shaderStage, hlslVersion);
	result = std::wstring(castingValue.begin(), castingValue.end());
	argList->push_back(result);

	if (outputTarget == OutputTarget::SPV)
	{
		argList->push_back(L"-spirv");
		castingValue = BuildVulkanVersion(VulkanVersion);
		result = std::wstring(castingValue.begin(), castingValue.end());
		argList->push_back(result);

	}

	argList->push_back(L"-E");
	Json::Value solution = *SolutionParser::GetSolution();
	std::string constMapResolver;
	auto it = s_EntrypointMapper.find(shaderStage);
	if (it != s_EntrypointMapper.end())
		constMapResolver = solution["GraphicsPipeline"][it->second.data()].asString();
	argList->push_back(std::wstring(constMapResolver.begin(), constMapResolver.end()));
	if (buildMode == BuildMode::DEBUG) {
		argList->push_back(L"-Od");
		argList->push_back(L"-Zi");
	}
	else {
		argList->push_back(L"-O3");
		argList->push_back(L"-Zs");
	}
}

std::string HLSLBuilder::GraphicsSource::BuildShaderStageName(ShaderStage shaderStage, Version hlslVersion)
{
	std::stringstream buffer;
	static const std::unordered_map<ShaderStage, std::string_view> entrypointMapper =
	{
		{ ShaderStage::Vertex, "vs" },
		{ ShaderStage::Pixel, "ps" }
	};

	auto it = entrypointMapper.find(shaderStage);
	if (it != entrypointMapper.end())
		buffer << it->second.data();

	buffer << "_" << hlslVersion.Major << "_" << hlslVersion.Minor;
	return buffer.str();
}

std::string HLSLBuilder::GraphicsSource::BuildExtensionName(ShaderStage shaderStage, OutputTarget outputTarget)
{
	std::stringstream buffer;
	static const std::unordered_map<ShaderStage, std::string_view> stageMapper =
	{
		{ ShaderStage::Vertex, "vs" },
		{ ShaderStage::Pixel, "ps" }
	};

	buffer << ".gp.";
	auto it = stageMapper.find(shaderStage);
	if (it != stageMapper.end())
		buffer << it->second.data();

	if (outputTarget == OutputTarget::SPV)
		buffer << ".spv";
	else
		buffer << ".cso";

	return buffer.str();
}

std::string HLSLBuilder::GraphicsSource::BuildVulkanVersion(Version vulkanVersion)
{
	std::stringstream buffer;
	buffer << "-fspv-target-env=vulkan" << vulkanVersion.Major << "." << vulkanVersion.Minor;
	return buffer.str();
}

std::string HLSLBuilder::GraphicsSource::BuildBlobRelativePath(ShaderStage shaderStage, OutputTarget outputTarget)
{
	std::string outputExtension = BuildExtensionName(shaderStage, outputTarget);
	std::stringstream fileOut;
	std::string constMapResolver;
	Json::Value solution = *(SolutionParser::GetSolution());
	std::filesystem::path relativeOut = std::filesystem::relative(std::filesystem::path(m_ParentPath), std::filesystem::path(solution["RunningPath"].asString()));
	std::string relativeOutResult = relativeOut.string();
	std::replace(relativeOutResult.begin(), relativeOutResult.end(), '.', '\0');
	
	if (strncmp(relativeOutResult.c_str(), "", 2) != 0)
		fileOut << "./" << relativeOutResult << "/" << m_BaseName << outputExtension.c_str();
	else
		fileOut << "./" << m_BaseName << outputExtension.c_str();
	auto it = s_FileEndpointMapper.find(shaderStage);
	if (it != s_FileEndpointMapper.end())
		constMapResolver = it->second.data();
	m_Properties[constMapResolver] = fileOut.str();
	return fileOut.str();
}

void HLSLBuilder::GraphicsSource::RegisterBlob(ShaderStage shaderStage, OutputTarget outputTarget)
{
	BuildMessage(shaderStage);
	std::string fileOut = BuildBlobRelativePath(shaderStage, OutputTarget::CSO);
	FileHandler::WriteBinFile(fileOut.c_str(), reinterpret_cast<std::byte*>(m_Blobs[shaderStage]->GetBufferPointer()), m_Blobs[shaderStage]->GetBufferSize());
	//Console::Log("{0} successfully compiled", fileOut.str());
}

const Json::Value* HLSLBuilder::GraphicsSource::GetProperties() const
{
	return &m_Properties;
}

void HLSLBuilder::GraphicsSource::ValidateStage(ShaderStage stage, bool present)
{
	std::stringstream buffer;
	static const std::unordered_map<ShaderStage, std::string_view> entrypointMapper =
	{
		{ ShaderStage::Vertex, "Vertex" },
		{ ShaderStage::Pixel, "Pixel" }
	};

	if (((stage == ShaderStage::Vertex) || (stage == ShaderStage::Pixel)) && !present)
	{
		auto it = entrypointMapper.find(stage);
		if (it != entrypointMapper.end())
			buffer << it->second.data();

		buffer << " Stage is mandatory";
		throw InvalidGraphicsPipelineException(buffer.str());
	}
}

void HLSLBuilder::GraphicsSource::SetCallback(std::function<void(std::string)> callback)
{
	m_Callback = callback;
}

std::string HLSLBuilder::GraphicsSource::GetBuildPath() const
{
	std::string sourcepath = (std::filesystem::path(m_ParentPath) / std::filesystem::path(m_BaseName)).string();
	std::replace(sourcepath.begin(), sourcepath.end(), '\\', '/');
	return sourcepath;
}

void HLSLBuilder::GraphicsSource::BuildMessage(ShaderStage stage)
{
	std::stringstream buffer;
	static const std::unordered_map<ShaderStage, std::string_view> entrypointMapper =
	{
		{ ShaderStage::Vertex, "Vertex" },
		{ ShaderStage::Pixel, "Pixel" }
	};

	buffer << "Building ";

	auto it = entrypointMapper.find(stage);
	if (it != entrypointMapper.end())
		buffer << it->second.data();

	buffer << " Stage";
	m_Callback(buffer.str());
}

HLSLBuilder::InvalidGraphicsPipelineException::InvalidGraphicsPipelineException(std::string message)
{
	m_Exception = message;
}
