#include <gtest/gtest.h>
#include <iostream>
#include <glslbuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	void ResolveArgList();

	TEST(GLSLBuilder, MissingSolutionFile)
	{
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_TRUE(controlArgs.empty());
	}

	TEST(GLSLBuilder, MismatchSolutionExtension)
	{
		ArgList::PushRawArg("--build:./uchigatana");
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs), GLSLBuilder::MismatchSolutionFileExtensionException);
	}

	TEST(GLSLBuilder, SolutionFileNotFound)
	{
		ArgList::PushRawArg("--build:./assets/project_sample.gls2");
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs), GLSLBuilder::SolutionFileNotFoundException);
	}

	TEST(GLSLBuilder, ValidBuildArgs)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/project.gls2");
		std::string message;
		ResolveArgList();

		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		auto build_args = GLSLBuilder::ArgParser::GetBuildInfos();
		ASSERT_STREQ(build_args.m_SolutionFilepath.c_str(), "./assets/test_sample/project.gls2");
	}

	void ResolveArgList()
	{
		ASSERT_NO_THROW(ArgList::ResolveArgs());
	}
}
