#pragma once

#include <string>
#include "GLSLBuilderAPI.hh"

namespace GLSLBuilder
{
	class GLSLB_API StringHandler
	{
	public:
		static void ToLower(std::string* content);
		static void ToUpper(std::string* content);
	};
}