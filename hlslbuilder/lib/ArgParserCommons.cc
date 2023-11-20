#include "ArgParserCommons.hh"

HLSLBuilder::MissingSolutionFileException::MissingSolutionFileException()
{
	m_Exception = "Missing build file";
}

HLSLBuilder::MismatchSolutionFileExtensionException::MismatchSolutionFileExtensionException()
{
	m_Exception = "The only accepted extension is \".hls2\"";
}

HLSLBuilder::SolutionFileNotFoundException::SolutionFileNotFoundException()
{
	m_Exception = "Build file not found in given path";
}