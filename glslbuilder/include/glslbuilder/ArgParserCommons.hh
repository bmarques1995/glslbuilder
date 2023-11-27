#pragma once

#include "CommonExceptions.hh"

namespace GLSLBuilder
{
	/**
	* Contains all infos to build the project:
	*	* SolutionPreProcessor file: *.gls2
	*/
	struct GLSLB_API BuildInfos
	{
	public:
		std::string m_SolutionFilepath;

		BuildInfos() :
			m_SolutionFilepath(".")
		{

		}

		BuildInfos(const std::string& filepath) :
			m_SolutionFilepath(filepath)
		{

		}
	};

	/**
	* Common exception of solution file, mother class for these 3 exception:
	*	* MissingSolutionFileException
	*   * MismatchSolutionFileExtensionException
	*   * SolutionFileNotFoundException
	*/
	class GLSLB_API SolutionFileException : public GLSLBuilderException
	{
	};

	/**
	* Thrown when the -b arg is not set.
	*/
	class GLSLB_API MissingSolutionFileException : public SolutionFileException
	{
	public:
		MissingSolutionFileException();
	};

	/**
	* Thrown when the extension doesn't match ".gls2".
	*/
	class GLSLB_API MismatchSolutionFileExtensionException : public SolutionFileException
	{
	public:
		MismatchSolutionFileExtensionException();
	};

	/**
	* Thrown when the ".gls2" file is not found.
	*/
	class GLSLB_API SolutionFileNotFoundException : public SolutionFileException
	{
	public:
		SolutionFileNotFoundException();
	};
}