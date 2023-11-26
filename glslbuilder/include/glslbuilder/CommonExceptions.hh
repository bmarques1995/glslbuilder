#pragma once

#include <exception>
#include <string>
#include "GLSLBuilderAPI.hh"

namespace GLSLBuilder
{
	class GLSLB_API HLSLBuilderException : public std::exception
	{
	public:
		const char* what() const override;
	protected:
		std::string m_Exception = "Default GLSLBuilder exception";
	};
}