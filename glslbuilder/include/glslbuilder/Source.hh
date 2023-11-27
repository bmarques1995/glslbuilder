#pragma once

#include "GLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <json/json.h>
#include <unordered_map>
#include <functional>

namespace GLSLBuilder
{
	/*
	* Displays the currently supported shader stages
	*/
	enum class ShaderStage
	{
		Vertex = 0,
		Pixel
	};

	class GLSLB_API Source
	{
	public:
		virtual void PreprocessShaders() = 0;
		virtual const Json::Value* GetProperties() const = 0;
		virtual void ValidateStage(ShaderStage stage, bool present) = 0;
		virtual void SetCallback(std::function<void(std::string)> callback) = 0;
		virtual std::string GetBuildPath() const = 0;
	protected:
		static const std::unordered_map<ShaderStage, std::string_view> s_EntrypointMapper;
	};
	
	class GLSLB_API InvalidPipelineException : public GLSLBuilderException
	{
	
	};
}