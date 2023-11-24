#pragma once

#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <json/json.h>
#include <unordered_map>
#include <functional>

namespace HLSLBuilder
{
	/*
	* Displays the currently supported shader stages
	*/
	enum class ShaderStage
	{
		Vertex = 0,
		Pixel
	};

	class HLSLB_API Source
	{
	public:
		virtual void CompileShaders(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion) = 0;
		virtual const Json::Value* GetProperties() const = 0;
		virtual void ValidateStage(ShaderStage stage, bool present) = 0;
		virtual void SetCallback(std::function<void(std::string)> callback) = 0;
		virtual std::string GetBuildPath() const = 0;
	protected:
		static const std::unordered_map<ShaderStage, std::string_view> s_EntrypointMapper;
	};
	
	class HLSLB_API InvalidPipelineException : public HLSLBuilderException
	{
	
	};
}