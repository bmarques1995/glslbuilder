#pragma once

#include <exception>
#include <string>
#include "HLSLBuilderAPI.hh"

namespace HLSLBuilder
{
	class HLSLB_API HLSLBuilderException : public std::exception
	{
	public:
		const char* what() const override;
	protected:
		std::string m_Exception = "Default HLSLBuilder exception";
	};
}