#include <gtest/gtest.h>
#include <iostream>
#include <GLSLBuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	extern void ResolveArgList();

	TEST(GLSLBuilder, ValidD3DCCSOSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validD3DCSources.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(GLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(GLSLBuilder, ValidDXCCSOSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validDXCSources.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(GLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(GLSLBuilder, ValidDXCSPVSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validDXCSources.hls2");
		ArgList::PushRawArg("-api:SPV");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(GLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(GLSLBuilder, D3DCGraphicsSourceError)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/errorSourcesD3DC.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_THROW(GLSLBuilder::Builder::BuildSources(), CompileErrorException);
		
		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(GLSLBuilder, DXCGraphicsSourceError)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/errorSourcesDXC.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = GLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(GLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = GLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(GLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *GLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(GLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_THROW(GLSLBuilder::Builder::BuildSources(), CompileErrorException);

		SolutionParser::Clear();
		Builder::Clear();
	}
}