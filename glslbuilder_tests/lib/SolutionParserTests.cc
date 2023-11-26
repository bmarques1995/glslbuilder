#include <gtest/gtest.h>
#include <iostream>
#include <GLSLBuilder/GLSLBuilder.hh>


namespace GLSLBuilder
{
	extern void ResolveArgList();

	TEST(GLSLBuilder, MissingPropertiesGLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidProperties.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::PropertyNotFoundException);
	}

	TEST(GLSLBuilder, InvalidNameGLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidName.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::InvalidNameException);
	}

	TEST(GLSLBuilder, InvalidPathGLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidPath.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::SourceNotFoundException);
	}

	TEST(GLSLBuilder, InvalidArrayGLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/invalidArray.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath), GLSLBuilder::InvalidArrayException);
	}

	TEST(GLSLBuilder, ValidGLS2)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/valid.gls2");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));
		auto value = 5u;
	}
}
