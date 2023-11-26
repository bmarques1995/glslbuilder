#include "ArgParserCommons.hh"

GLSLBuilder::MissingSolutionFileException::MissingSolutionFileException()
{
	m_Exception = "Missing build file";
}

GLSLBuilder::MismatchSolutionFileExtensionException::MismatchSolutionFileExtensionException()
{
	m_Exception = "The only accepted extension is \".hls2\"";
}

GLSLBuilder::SolutionFileNotFoundException::SolutionFileNotFoundException()
{
	m_Exception = "Build file not found in given path";
}