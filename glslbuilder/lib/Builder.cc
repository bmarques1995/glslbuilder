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
	for (unsigned i = 0; i < solution["TextSources"].size(); i++)
	{
		std::filesystem::path tempPath(solution["TextSources"][i].asString());
		if (tempPath.is_absolute())
		{
			std::string sourcePath = tempPath.string();
			std::replace(sourcePath.begin(), sourcePath.end(), '\\', '/');
			TextSource src(sourcePath);
			s_TextSources.push_back(src);
		}
		else
		{
			std::regex pattern("^(\\.\\\\|\\./|\\\\|/)");
			std::string pathStr = solution["TextSources"][i].asString();
			std::string result;
			result = std::regex_replace(pathStr, pattern, "");
			std::string sourcePath =
				(std::filesystem::path(solution["RunningPath"].asString()) / std::filesystem::path(result)).string();
			std::replace(sourcePath.begin(), sourcePath.end(), '\\', '/');
			TextSource src(sourcePath);
			s_TextSources.push_back(src);
		}
	}
}

void GLSLBuilder::Builder::BuildSources()
{
	uint32_t count = 0u;
	for (auto& i : s_TextSources)
	{
		SendBuildMessage(i);
		i.PreprocessShaders();
		s_Output["GraphicsShaders"][count] = *(i.GetProperties());
		count++;
	}
	Json::Value solution = *(SolutionParser::GetSolution());
	std::stringstream outputFile;
	outputFile << solution["ProjectName"].asString();
	outputFile << ".txtc";
	outputFile << ".json";
	std::filesystem::path outputPath = std::filesystem::path(solution["RunningPath"].asString()) / std::filesystem::path(outputFile.str());
	FileHandler::WriteTextFile(outputPath.string(), s_Output.toStyledString().c_str());
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
