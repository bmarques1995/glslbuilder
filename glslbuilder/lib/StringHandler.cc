#include "Utils/StringHandler.hh"

void GLSLBuilder::StringHandler::ToLower(std::string* content)
{
	for (std::string::iterator it = content->begin(); it != content->end(); it++)
	{
		*it = std::tolower(*it);
	}
}

void GLSLBuilder::StringHandler::ToUpper(std::string* content)
{
	for (std::string::iterator it = content->begin(); it != content->end(); it++)
	{
		*it = std::toupper(*it);
	}
}