#include <gtest/gtest.h>
#include <iostream>
#include <glslbuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	void ResolveArgList();

	TEST(GLSLBuilder, MissingSolutionFile)
	{
		ArgList::PushRawArg("-api:CSO");
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs), GLSLBuilder::MissingSolutionFileException);
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
		ArgList::PushRawArg("--build:./assets/project_sample.hls2");
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs), GLSLBuilder::SolutionFileNotFoundException);
	}

	TEST(GLSLBuilder, ValidBuildArgs)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/project.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();

		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();
		ArgList::ClearArgs();
		ASSERT_FALSE(controlArgs.empty());
		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		auto build_args = GLSLBuilder::ArgParser::GetBuildInfos();
		ASSERT_EQ(build_args.m_OutputTarget, OutputTarget::CSO);
		ASSERT_EQ(build_args.m_BuildMode, BuildMode::RELEASE);
		ASSERT_STREQ(build_args.m_SolutionFilepath.c_str(), "./assets/test_sample/project.hls2");
	}

	void ResolveArgList()
	{
		ASSERT_NO_THROW(ArgList::ResolveArgs());
	}
}