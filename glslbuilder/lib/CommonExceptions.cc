#include "CommonExceptions.hh"

const char* GLSLBuilder::GLSLBuilderException::what() const
{
	return m_Exception.c_str();
}
