#pragma once

#include "Source.hh"

namespace GLSLBuilder
{
	class TextSource : public Source
	{
	public:
		void PreprocessShaders() override;
		const Json::Value* GetProperties() const override;
		void ValidateStage(ShaderStage stage, bool present) override;
		void SetCallback(std::function<void(std::string)> callback) override;
		std::string GetBuildPath() const override;
	};
}