#pragma once

#include "GLSLBuilderAPI.hh"
#include "SolutionParserCommons.hh"
#include <json/json.h>
#include <list>
#include <utility>

namespace GLSLBuilder
{
	

	/**
	* The SolutionParser is the static class responsible to parse the .hls2 input file to a JSON Object.
	*
	* The complete description of HLS2 can be found [here](@ref docs/hls2.md).
	*/
	class GLSLB_API SolutionParser
	{
	public:
		/**
		* LoadProject is responsible to load the `.hls2` to a JSON object, and throws a PropertyNotFoundException if a mandatory property is missing.
		*/
		static void LoadProject(std::string_view path);
		/**
		* GetSolution returns the current HLS2 instance.
		*/
		static const Json::Value* GetSolution();

		static void Clear();
	private:
		static void ValidateJSONProperties();
		static void ValidateProperty(std::pair<std::string, GLSLBuilder::PropertyType> property);
		static void ValidatePropertyType(Json::Value& innerProperties, PropertyType property, std::string_view key);
		static void ValidateName(std::string_view name);
		static void ValidatePath(std::string path);
		static void ValidatePathArray(Json::Value& innerProperties, std::string_view key);
		static Json::Value s_GLS2Solution;
		static const std::list<std::pair<std::string, PropertyType>> s_ValidProperties;
	};
}