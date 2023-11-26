#pragma once

#include <GLSLBuilder.hh>
#include <functional>
#include "Console.hh"

namespace GLSLBuilderCLI
{
	class Helper
	{
	public:
		static void Resolve(GLSLBuilder::ArgCategory category);
		static void MultipleInfoError();
		static void InfoControlError();
	private:
		static const std::unordered_map<GLSLBuilder::ArgCategory, std::function<void()>> s_ArgResolvers;
	};
}