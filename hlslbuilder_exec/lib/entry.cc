#include <iostream>
#include "Console.hh"
#include "Helper.hh"
#include <hlslbuilder/CommonExceptions.hh>
#include <hlslbuilder/HLSLBuilder.hh>

static void BuildCommand();
static void Callback(std::string value);

int main(int argc, char** argv)
{
	HLSLBuilderCLI::Console::Init();
	HLSLBuilderCLI::Console::Log("Hello HLSLBuilder, your version is: {0}", HLSLBuilder::HLSLBuilderVersion);
	for (size_t i = 1; i < argc; i++)
	{
		HLSLBuilder::ArgList::PushRawArg(argv[i]);
	}
	try
	{
		BuildCommand();
	}
	catch (HLSLBuilder::ArgException e)
	{
		HLSLBuilderCLI::Console::Critical("{0}\n", e.what());
		HLSLBuilderCLI::Helper::Resolve(HLSLBuilder::ArgCategory::HELP);
		exit(2);
	}
	catch (const HLSLBuilder::SolutionFileException& e)
	{
		HLSLBuilderCLI::Console::Critical("{0}\n", e.what());
		exit(1);
	}
	catch (HLSLBuilder::HLSLBuilderException e) 
	{
		HLSLBuilderCLI::Console::Error(e.what());
		exit(3);
	}
	HLSLBuilder::ArgList::ClearArgs();
	HLSLBuilder::SolutionParser::Clear();
	HLSLBuilder::Builder::Clear();
	HLSLBuilderCLI::Console::End();
	return 0;
}

void BuildCommand()
{
	HLSLBuilder::ArgList::ResolveArgs();
	auto infoArg = HLSLBuilder::ArgList::GetInfoArg();
	auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();
	HLSLBuilder::ArgParser::SetControlArgs(controlArgs);
	if (!controlArgs.empty())
	{
		HLSLBuilder::ArgParser::SetControlArgs(controlArgs);
	}
	else
	{
		HLSLBuilderCLI::Helper::Resolve(infoArg);
	}
	auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();
	HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath);
	Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
	HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget);
	HLSLBuilder::Builder::SetCallback(std::bind(&Callback, std::placeholders::_1));
	HLSLBuilder::Builder::BuildSources();
}

static void Callback(std::string value)
{
	HLSLBuilderCLI::Console::Log(value);
}
