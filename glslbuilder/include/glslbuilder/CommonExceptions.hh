#pragma once

#include <exception>
#include <string>
#include "GLSLBuilderAPI.hh"

namespace GLSLBuilder
{
	/**
	* This is the root exception, that controls all childs.
	*/
	class GLSLB_API GLSLBuilderException : public std::exception
	{
	public:
		const char* what() const override;
	protected:
		std::string m_Exception = "Default GLSLBuilder exception";
	};
}