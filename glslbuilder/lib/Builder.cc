#include "Builder.hh"
#include <sstream>
#include <filesystem>
#include <regex>
#include "Utils/FileHandler.hh"
#include "SolutionParser.hh"

std::list<GLSLBuilder::TextSource> GLSLBuilder::Builder::s_TextSources;
Json::Value GLSLBuilder::Builder::s_Output;
std::function<void(std::string)> GLSLBuilder::Builder::s_Callback = [](std::string value){};

void GLSLBuilder::Builder::SetBuildArgs(Json::Value& solution)
{
	
}

void GLSLBuilder::Builder::BuildSources()
{
	
}

void GLSLBuilder::Builder::Clear()
{
	s_TextSources.clear();
}

void GLSLBuilder::Builder::SetCallback(std::function<void(std::string)> callback)
{
	s_Callback = callback;
	for (auto& i : s_TextSources)
	{
		i.SetCallback(callback);
	}
}

void GLSLBuilder::Builder::SendBuildMessage(const Source& source)
{
	std::stringstream buffer;
	buffer << "Building file: " << source.GetBuildPath();
	s_Callback(buffer.str());
}
