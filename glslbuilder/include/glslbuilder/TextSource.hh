#pragma once

#include "Source.hh"

namespace GLSLBuilder
{
	class TextSource : public Source
	{
	public:
		TextSource(std::string_view path);

		void PreprocessShaders() override;
		const Json::Value* GetProperties() const override;
		void ValidateStage(ShaderStage stage, bool present) override;
		void SetCallback(std::function<void(std::string)> callback) override;
		std::string GetBuildPath() const override;
	private:
		std::string m_BaseName;
		std::string m_SourceCode;
		std::string m_ParentPath;

		Json::Value m_Properties;
		std::unordered_map<ShaderStage, std::string> m_ProcessedShaders;
		std::function<void(std::string)> m_Callback;

		static const std::unordered_map<ShaderStage, std::string_view> s_FileEndpointMapper;
	};
}