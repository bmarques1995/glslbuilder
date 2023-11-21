#include "SolutionParser.hh"
#include "SolutionParser.hh"
#include "SolutionParser.hh"
#include <iostream>
#include <sstream>
#include "Utils/FileHandler.hh"
#include <filesystem>
#include <regex>

Json::Value HLSLBuilder::SolutionParser::s_HLS2Solution;
const std::list<std::pair<std::string, HLSLBuilder::PropertyType>> HLSLBuilder::SolutionParser::s_ValidProperties =
{
	{ "GraphicsPipelineSources", HLSLBuilder::PropertyType::PATH_ARRAY },
	{ "GraphicsPipeline->VertexEntry", HLSLBuilder::PropertyType::NAME },
	{ "GraphicsPipeline->PixelEntry", HLSLBuilder::PropertyType::NAME },
	//{ "GraphicsPipeline->GeometryEntry", HLSLBuilder::PropertyType::NAME },
	//{ "GraphicsPipeline->DomainEntry", HLSLBuilder::PropertyType::NAME },
	//{ "GraphicsPipeline->HullEntry", HLSLBuilder::PropertyType::NAME },
	{ "VulkanVersion", HLSLBuilder::PropertyType::VERSION },
	{ "HLSLVersion", HLSLBuilder::PropertyType::VERSION }
};

void HLSLBuilder::SolutionParser::LoadProject(std::string_view path)
{
	std::string json_text;
	FileHandler::ReadTextFile(path, &json_text);
	Json::Reader jsonReader;
	jsonReader.parse(json_text, s_HLS2Solution);
	std::string absolutePath = std::filesystem::absolute(path).parent_path().string();
	std::replace(absolutePath.begin(), absolutePath.end(), '\\', '/');
	s_HLS2Solution["RunningPath"] = absolutePath;
	s_HLS2Solution["ProjectName"] = std::filesystem::absolute(path).stem().string();
	ValidateJSONProperties();
}

const Json::Value* HLSLBuilder::SolutionParser::GetSolution()
{
	return &s_HLS2Solution;
}

void HLSLBuilder::SolutionParser::ValidateJSONProperties()
{
	for (auto it = s_ValidProperties.begin(); it != s_ValidProperties.end(); it++)
		ValidateProperty(*it);
}

void HLSLBuilder::SolutionParser::ValidateVersion(std::string_view version)
{
	std::string arg = version.data();
	std::regex pattern("^[0-9]+\\.[0-9]+$");

	if (!std::regex_match(arg, pattern))
		throw InvalidVersionException(version);
}

void HLSLBuilder::SolutionParser::ValidateName(std::string_view name)
{
	std::string arg = name.data();
	std::regex pattern("^[a-zA-Z_][a-zA-Z0-9_]*$");

	if (!std::regex_match(arg, pattern))
		throw InvalidNameException(name);
}

void HLSLBuilder::SolutionParser::ValidatePath(std::string path)
{
	std::regex pattern("^(\\.\\\\|\\./|\\\\|/)");
	std::string result;
	std::filesystem::path temp(path);
	std::filesystem::path fullPath;
	if (temp.is_absolute())
	{
		result = temp.string();
		fullPath = std::filesystem::path(result);
	}
	else
	{
		result = std::regex_replace(path, pattern, "");
		fullPath = std::filesystem::path(s_HLS2Solution["RunningPath"].asString()) / std::filesystem::path(result);
	}
	if (!std::filesystem::is_regular_file(fullPath))
		throw SourceNotFoundException(fullPath.string());
}

void HLSLBuilder::SolutionParser::ValidatePathArray(Json::Value& innerProperties, std::string_view key)
{
	if (innerProperties[key.data()].isArray())
	{
		for (unsigned i = 0; i < innerProperties[key.data()].size(); i++)
		{
			ValidatePath(innerProperties[key.data()][i].asString());
		}
	}
	else
	{
		throw InvalidArrayException();
	}
}

void HLSLBuilder::SolutionParser::ValidateProperty(std::pair<std::string, HLSLBuilder::PropertyType> property)
{
	std::string text = property.first;
	std::regex pattern("->");
	std::sregex_token_iterator matcher(text.begin(), text.end(), pattern, -1);
	std::sregex_token_iterator end;
	Json::Value innerProperties = s_HLS2Solution;
	for (auto it = matcher; it != end; ++it)
	{
		if (std::distance(it, end) > 1)
		{
			std::string key = it->str();
			bool valid = innerProperties.isMember(key);
			if (!valid)
				throw PropertyNotFoundException(property.first);
			innerProperties = innerProperties[key.c_str()];
		}
		else
		{
			std::string key = it->str();
			bool valid = innerProperties.isMember(key);
			if (!valid)
				throw PropertyNotFoundException(property.first);
			ValidatePropertyType(innerProperties, property.second, key);
		}
	}
}

void HLSLBuilder::SolutionParser::ValidatePropertyType(Json::Value& innerProperties, PropertyType property, std::string_view key)
{
	switch (property)
	{
	case PropertyType::NAME:
		ValidateName(innerProperties[key.data()].as<std::string>());
		break;
	case PropertyType::PATH_ARRAY:
	{
		ValidatePathArray(innerProperties, key);
		break;
	}
	case PropertyType::VERSION:
		ValidateVersion(innerProperties[key.data()].as<std::string>());
		break;
	default:
		break;
	}
}
