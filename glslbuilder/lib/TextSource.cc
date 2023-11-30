#include "TextSource.hh"
#include "Utils/FileHandler.hh"
#include <filesystem>
#include "SolutionParser.hh"

const std::unordered_map<GLSLBuilder::ShaderStage, std::string_view> GLSLBuilder::TextSource::s_FileEndpointMapper =
{
	{ ShaderStage::Vertex, "VertexFile" },
	{ ShaderStage::Pixel, "PixelFile" }
};

const std::unordered_map<GLSLBuilder::ShaderStage, std::string_view> GLSLBuilder::TextSource::s_FileEntrypointMapper =
{
	{ ShaderStage::Vertex, "VertexEntry" },
	{ ShaderStage::Pixel, "PixelEntry" }
};

GLSLBuilder::TextSource::TextSource(std::string_view path)
{
	FileHandler::ReadTextFile(path, &m_SourceCode);
	std::filesystem::path pathName(path.data());
	m_BaseName = pathName.stem().string();
	m_Properties["BaseName"] = m_BaseName;
	m_ParentPath = pathName.parent_path().string();
	std::replace(m_ParentPath.begin(), m_ParentPath.end(), '\\', '/');
}

void GLSLBuilder::TextSource::PreprocessShaders()
{
	PreprocessWithStage(ShaderStage::Vertex);
	PreprocessWithStage(ShaderStage::Pixel);
}

const Json::Value* GLSLBuilder::TextSource::GetProperties() const
{
	return &m_Properties;
}

void GLSLBuilder::TextSource::ValidateStage(ShaderStage stage, bool present)
{
}

void GLSLBuilder::TextSource::SetCallback(std::function<void(std::string)> callback)
{
}

std::string GLSLBuilder::TextSource::GetBuildPath() const
{
	return std::string();
}

void GLSLBuilder::TextSource::PreprocessWithStage(ShaderStage shaderStage)
{
	bool stageFound = false;
	std::istringstream stream(m_SourceCode);
	std::string line;
	Json::Value solution = *SolutionParser::GetSolution();
	std::string stageName;
	auto it = s_FileEntrypointMapper.find(shaderStage);
	if (it != s_FileEntrypointMapper.end())
		stageName = solution["GraphicsPipeline"][it->second.data()].asString();

	std::ostringstream result;

	// Read lines until newline character
	while (std::getline(stream, line, '\n')) {
		std::replace(line.begin(), line.end(), '\r', '\0');
		if (line[line.length() - 1] == '\0')
			line.pop_back();
		if (!m_EntrypointPreprocessor.EvaluateState(line))
		{
			bool expr = (m_EntrypointPreprocessor.GetStateNesting() == 1) && (stageName.compare(m_EntrypointPreprocessor.GetTopMacro()) == 0);
			if ((m_EntrypointPreprocessor.GetStateNesting() == 0) || expr)
			{
				result << line << "\n";
			}
			if (expr)
				stageFound = true;
		}
	}

	if (m_EntrypointPreprocessor.GetStateNesting() > 0)
		throw MissingEntrypointPoppingException();

	if (stageFound)
	{
		m_ProcessedShaders[shaderStage] = result.str();
		std::string fileOut = BuildTextRelativePath(shaderStage);
		FileHandler::WriteTextFile(fileOut.c_str(), result.str());
	}
}

std::string GLSLBuilder::TextSource::BuildExtensionName(GLSLBuilder::ShaderStage shaderStage)
{
	std::stringstream buffer;
	static const std::unordered_map<ShaderStage, std::string_view> stageMapper =
	{
		{ ShaderStage::Vertex, "vert" },
		{ ShaderStage::Pixel, "frag" }
	};

	buffer << ".gp.";
	auto it = stageMapper.find(shaderStage);
	if (it != stageMapper.end())
		buffer << it->second.data();

	return buffer.str();
}

std::string GLSLBuilder::TextSource::BuildTextRelativePath(ShaderStage shaderStage)
{
	std::string outputExtension = BuildExtensionName(shaderStage);
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
	std::filesystem::path registerPath = std::filesystem::path(m_ParentPath) / (fileOut.str());
	return registerPath.string();
}
