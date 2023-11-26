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

GLSLBuilder::InvalidHLSLVersionException::InvalidHLSLVersionException(Version version)
{
	std::stringstream buffer;
	buffer << "HLSL " << version.Major << "." << version.Minor << " isn't supported or do not exists";
	m_Exception = buffer.str();
}

GLSLBuilder::InvalidVulkanVersionException::InvalidVulkanVersionException(Version version)
{
	std::stringstream buffer;
	buffer << "Vulkan " << version.Major << "." << version.Minor << " isn't supported or do not exists";
	m_Exception = buffer.str();
}

GLSLBuilder::InvalidSPVSupportException::InvalidSPVSupportException()
{
	m_Exception = "Spir-V output is allowed only after HLSL 6.0";
}

GLSLBuilder::CompileErrorException::CompileErrorException(std::string error)
{
	m_Exception = error;
}