#include "BuilderCommons.hh"
#include <sstream>

GLSLBuilder::Version::Version() :
	Minor(0), Major(0)
{
}

GLSLBuilder::Version::Version(std::string version)
{
	std::istringstream iss(version);
	std::string token;
	try
	{
		std::getline(iss, token, '.');
		Major = std::stoul(token);
		std::getline(iss, token, '.');
		Minor = std::stoul(token);
	}
	catch (const std::out_of_range& e)
	{
		throw e;
	}
}

GLSLBuilder::Version::Version(unsigned major, unsigned minor) :
	Major(major), Minor(minor)
{

}

bool GLSLBuilder::Version::operator==(Version version) const
{
	return ((this->Major == version.Major) && (this->Minor == version.Minor));
}

std::string GLSLBuilder::Version::ToString() const
{
	std::string castedVersion;
	std::stringstream buffer;
	buffer << Major << "." << Minor;
	castedVersion = buffer.str();
	return castedVersion;
}
