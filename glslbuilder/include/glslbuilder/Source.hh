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

	/**
	* This class is the mother of all pipelines classes.
	*/
	class GLSLB_API Source
	{
	public:

		/**
		* This method is used to compile all shaders. In this project, is presumed (and tested) that all shaders are saved in the same file
		*/
		virtual void PreprocessShaders() = 0;
		
		/**
		* This method recovers all properties of the source:
		*/
		virtual const Json::Value* GetProperties() const = 0;
		
		/**
		* This method validates all stages, with the pipeline rules.
		*/
		virtual void ValidateStage(ShaderStage stage, bool present) = 0;
		
		/**
		* This method set the callback to the compiled shader.
		*/
		virtual void SetCallback(std::function<void(std::string)> callback) = 0;
		
		/**
		* This method get the path where the group will be built.
		*/
		virtual std::string GetBuildPath() const = 0;
	protected:
		static const std::unordered_map<ShaderStage, std::string_view> s_EntrypointMapper;
	};
	
	class GLSLB_API InvalidPipelineException : public GLSLBuilderException
	{
	
	};
}