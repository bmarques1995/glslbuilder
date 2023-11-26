#pragma once

#include <json/json.h>
#include <list>
#include <string>
#include "Source.hh"
#include "GLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <functional>

namespace GLSLBuilder
{
	class GLSLB_API Builder
	{
	public:
		static void SetBuildArgs(Json::Value& solution, BuildMode buildMode, OutputTarget outputTarget);
		static void BuildSources();

		static void Clear();
		static void SetCallback(std::function<void(std::string)> callback);
		static void SendBuildMessage(const Source& source);
	private:

		static void ValidateGLSLVersion();
		static void ValidateVulkanVersion();
		static void ValidateOutputTarget();

		static BuildMode s_BuildMode;
		static OutputTarget s_OutputTarget;
		//static std::list<GraphicsSource> s_GraphicsSources;
		static Version s_HLSLVersion;
		static Version s_VulkanVersion;
		static std::function<void(std::string)> s_Callback;

		static Json::Value s_Output;
	};
}