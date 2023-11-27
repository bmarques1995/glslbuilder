#pragma once

#include <json/json.h>
#include <list>
#include <string>
#include "TextSource.hh"
#include "GLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <functional>

namespace GLSLBuilder
{
	class GLSLB_API Builder
	{
	public:
		static void SetBuildArgs(Json::Value& solution);
		static void BuildSources();

		static void Clear();
		static void SetCallback(std::function<void(std::string)> callback);
		static void SendBuildMessage(const Source& source);
	private:
		static std::list<TextSource> s_TextSources;
		static std::function<void(std::string)> s_Callback;

		static Json::Value s_Output;
	};
}