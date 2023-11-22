#pragma once

#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include "Source.hh"
#include <wrl.h>
#include <dxcapi.h>

#ifdef HLSLB_WINDOWS
#include <d3dcompiler.h>
#endif

using Microsoft::WRL::ComPtr;

namespace HLSLBuilder
{
	class HLSLB_API GraphicsSource : public Source
	{
	public:
		GraphicsSource(std::string_view path);
		void CompileShaders(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion) override;
		const Json::Value* GetProperties() const override;
		void ValidateStages() override;

		void SetCallback(std::function<void(std::string)> callback) override;
		std::string GetBuildPath() const override;

		void BuildMessage(ShaderStage stage);
	private:

		void CompileD3DCGroup(BuildMode buildMode, Version HLSLVersion);
		void CompileDXCGroup(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion);
		
		void D3DCBuildShader(BuildMode buildMode, ShaderStage shaderStage, Version hlslVersion);
		void DXCBuildShader(BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion);

		void PushDxcArgList(std::vector<std::wstring>* argList, BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion);

		std::string BuildShaderStageName(ShaderStage shaderStage, Version hlslVersion);
		std::string BuildExtensionName(ShaderStage shaderStage, OutputTarget outputTarget);
		std::string BuildVulkanVersion(Version vulkanVersion);

		void RegisterBlob(ShaderStage shaderStage, OutputTarget outputTarget);

		std::string m_BaseName;
		std::string m_SourceCode;
		std::string m_ParentPath;

		Json::Value m_Properties;
		std::unordered_map<ShaderStage, ComPtr<IDxcBlob>> m_Blobs;
		std::function<void(std::string)> m_Callback;

		static const std::unordered_map<ShaderStage, std::string_view> s_FileEndpointMapper;
	};
}