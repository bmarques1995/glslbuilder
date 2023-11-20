#pragma once

#include <HLSLBuilder.hh>
#include <functional>
#include "Console.hh"

namespace HLSLBuilderCLI
{
	class Helper
	{
	public:
		static void Resolve(HLSLBuilder::ArgCategory category);
		static void MultipleInfoError();
		static void InfoControlError();
	private:
		static const std::unordered_map<HLSLBuilder::ArgCategory, std::function<void()>> s_ArgResolvers;
	};
}