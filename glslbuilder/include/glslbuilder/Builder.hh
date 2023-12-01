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
	/**
	* The Builder is the static class to wrap all necessary arguments to be sent to D3DCompiler (until HLSL 5.1) or DXC (since HLSL 6.0)
	*/
	class GLSLB_API Builder
	{
	public:

		/**
		* This method sets all infos, in JSON format, to be sent to the sources.
		*/
		static void SetBuildArgs(Json::Value& solution);
		
		/**
		* This method builds all sources on all Source Lists.
		*/
		static void BuildSources();


		/**
		* This method clears all source list.
		*/
		static void Clear();
		
		/**
		* This method sets the callback method when a shader is built.
		*/
		static void SetCallback(std::function<void(std::string)> callback);
		
		/**
		* This method calls the callback method.
		*/
		static void SendBuildMessage(const Source& source);
	private:
		static std::list<TextSource> s_TextSources;
		static std::function<void(std::string)> s_Callback;

		static Json::Value s_Output;
	};
}