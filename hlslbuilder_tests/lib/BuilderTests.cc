#include <gtest/gtest.h>
#include <iostream>
#include <HLSLBuilder/HLSLBuilder.hh>

namespace HLSLBuilder
{
	extern void ResolveArgList();

	TEST(HLSLBuilder, ValidD3DCCSOSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validD3DCSources.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(HLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(HLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(HLSLBuilder, ValidDXCCSOSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validDXCSources.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(HLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(HLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(HLSLBuilder, ValidDXCSPVSources)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/validDXCSources.hls2");
		ArgList::PushRawArg("-api:SPV");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(HLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_NO_THROW(HLSLBuilder::Builder::BuildSources());

		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(HLSLBuilder, D3DCGraphicsSourceError)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/errorSourcesD3DC.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(HLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_THROW(HLSLBuilder::Builder::BuildSources(), CompileErrorException);
		
		SolutionParser::Clear();
		Builder::Clear();
	}

	TEST(HLSLBuilder, DXCGraphicsSourceError)
	{
		ArgList::PushRawArg("--build:./assets/test_sample/errorSourcesDXC.hls2");
		ArgList::PushRawArg("-api:CSO");
		ArgList::PushRawArg("-c:Release");
		std::string message;
		ResolveArgList();
		auto controlArgs = HLSLBuilder::ArgList::GetControlArgs();

		ASSERT_NO_THROW(HLSLBuilder::ArgParser::SetControlArgs(controlArgs));
		ArgList::ClearArgs();

		auto parsedControlArgs = HLSLBuilder::ArgParser::GetBuildInfos();

		ASSERT_NO_THROW(HLSLBuilder::SolutionParser::LoadProject(parsedControlArgs.m_SolutionFilepath));

		Json::Value solution = *HLSLBuilder::SolutionParser::GetSolution();
		ASSERT_NO_THROW(HLSLBuilder::Builder::SetBuildArgs(solution, parsedControlArgs.m_BuildMode, parsedControlArgs.m_OutputTarget));
		ASSERT_THROW(HLSLBuilder::Builder::BuildSources(), CompileErrorException);

		SolutionParser::Clear();
		Builder::Clear();
	}
}