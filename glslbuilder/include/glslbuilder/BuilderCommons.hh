#pragma once

#include <string>
#include <exception>
#include "CommonExceptions.hh"

namespace GLSLBuilder
{
	struct Version
	{
		unsigned Major;
		unsigned Minor;

		Version();

		Version(std::string version);
		Version(unsigned major, unsigned minor);

		bool operator==(Version version) const;
		std::string ToString() const;
	};

	class CompilerException : public GLSLBuilderException
	{
	};

	class CompileErrorException : public CompilerException
	{
	public:
		CompileErrorException(std::string error);
	};
}