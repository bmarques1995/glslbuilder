#pragma once

#include <cstdint>
#include <string>

namespace GLSLBuilder
{
	class Preprocessor
	{
	public:
		virtual size_t GetStateNesting() const = 0;
		virtual std::string GetTopMacro() const = 0;
		//virtual void ValidateMacro(std::string_view name) = 0;
		virtual bool EvaluateState(std::string line) = 0;
	};
}
