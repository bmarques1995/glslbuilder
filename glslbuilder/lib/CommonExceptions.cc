#include "CommonExceptions.hh"

const char* GLSLBuilder::HLSLBuilderException::what() const
{
	return m_Exception.c_str();
}
