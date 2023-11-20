#include "CommonExceptions.hh"

const char* HLSLBuilder::HLSLBuilderException::what() const
{
	return m_Exception.c_str();
}
