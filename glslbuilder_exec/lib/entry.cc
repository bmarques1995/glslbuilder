#include <iostream>
#include "Console.hh"
#include "Helper.hh"
#include <glslbuilder/CommonExceptions.hh>
#include <glslbuilder/GLSLBuilder.hh>

static void BuildCommand();
static void Callback(std::string value);

int main(int argc, char** argv)
{
	GLSLBuilderCLI::Console::Init();
	GLSLBuilderCLI::Console::Log("Hello GLSLBuilder, your version is: {0}", GLSLBuilder::GLSLBuilderVersion);
	for (size_t i = 1; i < argc; i++)
	{
		GLSLBuilder::ArgList::PushRawArg(argv[i]);
	}
	try
	{
		BuildCommand();
	}
	catch (GLSLBuilder::ArgException e)
	{
		GLSLBuilderCLI::Console::Critical("{0}\n", e.what());
		GLSLBuilderCLI::Helper::Resolve(GLSLBuilder::ArgCategory::HELP);
		exit(2);
	}
	catch (const GLSLBuilder::SolutionFileException& e)
	{
		GLSLBuilderCLI::Console::Critical("{0}\n", e.what());
		exit(1);
	}
	catch (GLSLBuilder::GLSLBuilderException e) 
	{
		GLSLBuilderCLI::Console::Error(e.what());
		exit(3);
	}
	GLSLBuilder::ArgList::ClearArgs();
	GLSLBuilder::SolutionParser::Clear();
	GLSLBuilder::Builder::Clear();
	GLSLBuilderCLI::Console::End();
	return 0;
}

void BuildCommand()
{
	GLSLBuilder::ArgList::ResolveArgs();
	auto infoArg = GLSLBuilder::ArgList::GetInfoArg();
	auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
	GLSLBuilder::ArgParser::SetControlArgs(controlArgs);
	if (!controlArgs.empty())
	{
		GLSLBuilder::ArgParser::SetControlArgs(controlArgs);
	}
	else
	{
		GLSLBuilderCLI::Helper::Resolve(infoArg);
	}
	auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();
	GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath);
	Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
	GLSLBuilder::Builder::SetBuildArgs(solution);
	GLSLBuilder::Builder::SetCallback(std::bind(&Callback, std::placeholders::_1));
	GLSLBuilder::Builder::BuildSources();
}

static void Callback(std::string value)
{
	GLSLBuilderCLI::Console::Log(value);
}
