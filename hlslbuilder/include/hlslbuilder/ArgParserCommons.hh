#pragma once

#include "CommonExceptions.hh"

namespace HLSLBuilder
{
	enum class BuildMode
	{
		DEBUG = 0,
		RELEASE
	};

	enum class OutputTarget
	{
		SPV = 0,
		CSO
	};

	/**
	* Contains all infos to build the project:
	*	* SolutionPreProcessor file: *.hls2
	*   * Build mode: debug/release
	*   * Build api: spv(vulkan target)/cso(d3d target)
	*/
	struct HLSLB_API BuildInfos
	{
	public:
		BuildMode m_BuildMode;
		OutputTarget m_OutputTarget;
		std::string m_SolutionFilepath;

		BuildInfos() :
			m_SolutionFilepath("."),
			m_OutputTarget(OutputTarget::CSO),
			m_BuildMode(BuildMode::DEBUG)
		{

		}

		BuildInfos(const std::string& filepath, BuildMode buildMode = BuildMode::DEBUG, OutputTarget outputTarget = OutputTarget::CSO) :
			m_SolutionFilepath(filepath), m_BuildMode(buildMode), m_OutputTarget(outputTarget)
		{

		}
	};

	/**
	* Common exception of solution file, mother class for these 3 exception:
	*	* MissingSolutionFileException
	*   * MismatchSolutionFileExtensionException
	*   * SolutionFileNotFoundException
	*/
	class HLSLB_API SolutionFileException : public HLSLBuilderException
	{
	};

	/**
	* Thrown when the -b arg is not set.
	*/
	class HLSLB_API MissingSolutionFileException : public SolutionFileException
	{
	public:
		MissingSolutionFileException();
	};

	/**
	* Thrown when the extension doesn't match ".hls2".
	*/
	class HLSLB_API MismatchSolutionFileExtensionException : public SolutionFileException
	{
	public:
		MismatchSolutionFileExtensionException();
	};

	/**
	* Thrown when the ".hls2" file is not found.
	*/
	class HLSLB_API SolutionFileNotFoundException : public SolutionFileException
	{
	public:
		SolutionFileNotFoundException();
	};
}