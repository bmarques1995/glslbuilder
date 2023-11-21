#pragma once

#include <json/json.h>
#include <list>
#include <string>
#include "GraphicsSource.hh"
#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"

namespace HLSLBuilder
{
	class HLSLB_API Builder
	{
	public:
		static void SetBuildArgs(Json::Value& solution, BuildMode buildMode, OutputTarget outputTarget);
		static void BuildSources();

		static void Clear();
	private:

		static void ValidateHLSLVersion();
		static void ValidateVulkanVersion();
		static void ValidateOutputTarget();

		static BuildMode s_BuildMode;
		static OutputTarget s_OutputTarget;
		static std::list<GraphicsSource> s_GraphicsSources;
		static Version s_HLSLVersion;
		static Version s_VulkanVersion;

		static Json::Value s_Output;
	};
}