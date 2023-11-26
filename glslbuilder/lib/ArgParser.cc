#include "ArgParser.hh"
#include "Utils/StringHandler.hh"
#include <filesystem>

GLSLBuilder::BuildInfos GLSLBuilder::ArgParser::s_BuildInfos;

void GLSLBuilder::ArgParser::SetControlArgs(const std::list<std::pair<GLSLBuilder::ArgCategory, std::string>>& controlArgs)
{
	std::list<std::pair<GLSLBuilder::ArgCategory, std::string>> controlArgsCopy = controlArgs;
	std::unordered_map<GLSLBuilder::ArgCategory, std::string> mapControlArgs;
	while (!controlArgsCopy.empty())
	{
		auto val = controlArgsCopy.front();
		mapControlArgs[val.first] = val.second;
		controlArgsCopy.pop_front();
	}
	CastMapToBuildInfos(mapControlArgs);
}

GLSLBuilder::BuildInfos GLSLBuilder::ArgParser::GetBuildInfos()
{
	return s_BuildInfos;
}

void GLSLBuilder::ArgParser::CastMapToBuildInfos(std::unordered_map<GLSLBuilder::ArgCategory, std::string>& mappedArgs)
{
	if (mappedArgs.find(ArgCategory::BUILD) == mappedArgs.end())
		throw MissingSolutionFileException();

	std::string filepath = mappedArgs[ArgCategory::BUILD];

	ValidateFileExtension(filepath);
	FindFile(filepath);

	BuildMode buildMode = BuildMode::DEBUG;
	OutputTarget outputTarget = OutputTarget::CSO;

	if (mappedArgs.find(ArgCategory::CONFIG) != mappedArgs.end())
		buildMode = CastStringToBuildMode(mappedArgs[ArgCategory::CONFIG]);
	if (mappedArgs.find(ArgCategory::API) != mappedArgs.end())
		outputTarget = CastStringToOutputTarget(mappedArgs[ArgCategory::API]);

	s_BuildInfos = BuildInfos(filepath, buildMode, outputTarget);
}

void GLSLBuilder::ArgParser::ValidateFileExtension(std::string_view path)
{
	std::string filePath = path.data();
	std::regex extensionRegex(".*\\.([a-zA-Z0-9]+)$");
	std::smatch match;

	if (std::regex_match(filePath, match, extensionRegex)) {
		std::string extension = match.str(1);
		std::string expectedExtension = "gls2";
		if (expectedExtension.compare(extension) != 0)
		{
			throw MismatchSolutionFileExtensionException();
		}
	}
	else {
		throw MismatchSolutionFileExtensionException();
	}
}

void GLSLBuilder::ArgParser::FindFile(std::string_view path)
{
	if (!std::filesystem::exists(path))
		throw SolutionFileNotFoundException();
}

GLSLBuilder::BuildMode GLSLBuilder::ArgParser::CastStringToBuildMode(std::string strValue)
{
	const std::unordered_map<std::string, BuildMode> buildModeMap =
	{
		{ "debug", BuildMode::DEBUG },
		{ "release", BuildMode::RELEASE }
	};

	auto it = buildModeMap.find(strValue);
	if (it != buildModeMap.end())
		return it->second;
	else
		return BuildMode::DEBUG;

}

GLSLBuilder::OutputTarget GLSLBuilder::ArgParser::CastStringToOutputTarget(std::string strValue)
{
	const std::unordered_map<std::string, OutputTarget> outputTargetMap =
	{
		{ "cso", OutputTarget::CSO },
		{ "spv", OutputTarget::SPV }
	};

	auto it = outputTargetMap.find(strValue);
	if (it != outputTargetMap.end())
		return it->second;
	else
		return OutputTarget::CSO;
}
