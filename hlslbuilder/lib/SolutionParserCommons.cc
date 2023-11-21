#include "SolutionParserCommons.hh"

HLSLBuilder::PropertyNotFoundException::PropertyNotFoundException(std::string_view property)
{
	std::stringstream buffer;
	buffer << "Property: " << property.data() << " not found";
	m_Exception = buffer.str();
}

HLSLBuilder::InvalidVersionException::InvalidVersionException(std::string_view arg)
{
	std::stringstream buffer;
	buffer << "Argument: " << arg.data() << " is not a version argument, that follows the property <unsigned>.<unsigned>";
	m_Exception = buffer.str();
}

HLSLBuilder::InvalidNameException::InvalidNameException(std::string_view arg)
{
	std::stringstream buffer;
	buffer << "Argument: \"" << arg.data() << "\" is not a valid name, all names must start with a letter or \'_\' and can only be followed by letters, \'_\' or digits";
	m_Exception = buffer.str();
}

HLSLBuilder::SourceNotFoundException::SourceNotFoundException(std::string_view arg)
{
	std::stringstream buffer;
	buffer << "Source: " << arg.data() << " was not found";
	m_Exception = buffer.str();
}

HLSLBuilder::InvalidArrayException::InvalidArrayException()
{
	m_Exception = "The argument is not an array";
}
