#pragma once

#include "Source.hh"
#include "EntrypointPreprocessor.hh"

namespace GLSLBuilder
{
	/**
	* This Class Manages all Shaders on the Graphics Pipeline Config
	*  * Vertex
	*  * Fragment
	*  * Geometry
	*  * Tesselation Evaluation
	*  * Tesselation Control
	*/
	class GLSLB_API TextSource : public Source
	{
	public:

		/**
		* This class is built only with the path of the shader group
		*/
		TextSource(std::string_view path);

		/**
		* This method is used to preprocess all shaders. In this project, is presumed (and tested) that all shaders are saved in the same file
		*/
		void PreprocessShaders() override;
		
		/**
		* This method recovers all properties of the source:
		*  * BaseName
		*  * VertexFile
		*  * PixelFile
		*/
		const Json::Value* GetProperties() const override;
		
		/**
		* This method validates all stages, with the graphics pipeline rules.
		*/
		void ValidateStage(ShaderStage stage, bool present) override;
		
		/**
		* This method set the callback to the compiled shader.
		*/
		void SetCallback(std::function<void(std::string)> callback) override;
		
		/**
		* This method get the path where the group will be built.
		*/
		std::string GetBuildPath() const override;
	private:

		void PreprocessWithStage(ShaderStage shaderStage);
		std::string BuildExtensionName(GLSLBuilder::ShaderStage shaderStage);
		std::string BuildTextRelativePath(ShaderStage shaderStage);

		std::string m_BaseName;
		std::string m_SourceCode;
		std::string m_ParentPath;

		EntrypointPreprocessor m_EntrypointPreprocessor;
		Json::Value m_Properties;
		std::unordered_map<ShaderStage, std::string> m_ProcessedShaders;
		std::function<void(std::string)> m_Callback;

		static const std::unordered_map<ShaderStage, std::string_view> s_FileEndpointMapper;
		static const std::unordered_map<ShaderStage, std::string_view> s_FileEntrypointMapper;
	};

	/**
	* Exception thrown when the pipeline stage is invalid.
	*/
	class GLSLB_API InvalidGraphicsPipelineException : public PreprocessorException
	{
	public:
		InvalidGraphicsPipelineException(std::string message);
	};
}