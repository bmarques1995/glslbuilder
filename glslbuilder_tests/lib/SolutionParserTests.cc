#include <gtest/gtest.h>
#include <iostream>
#include <GLSLBuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	extern void ResolveArgList();

	TEST(GLSLBuilder, MissingPropertiesHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidProperties.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::PropertyNotFoundException);
	}

	TEST(GLSLBuilder, InvalidNameHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidName.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::InvalidNameException);
	}

	TEST(GLSLBuilder, InvalidVersionHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidVersion.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::InvalidVersionException);
	}

	TEST(GLSLBuilder, InvalidPathHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidPath.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::SourceNotFoundException);
	}

	TEST(GLSLBuilder, InvalidArrayHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidArray.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::InvalidArrayException);
	}

	TEST(GLSLBuilder, ValidHLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/valid.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));
	}
}