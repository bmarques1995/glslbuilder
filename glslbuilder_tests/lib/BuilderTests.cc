#include <gtest/gtest.h>
#include <iostream>
#include <GLSLBuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	extern void ResolveArgList();

	TEST(GLSLBuilder, ValidSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validSources.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution));
		ASSERT_NO_THROW(GLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}
}
