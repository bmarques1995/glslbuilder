#pragma once

#include <cstdint>
#include <string>

namespace GLSLBuilder
{
	/**
	* Base class of preprocessors, like include or define
	*/
	class Preprocessor
	{
	public:
		/**
		* Get the number of pushed macro nested
		* Like multiple #ifdef
		*/
		virtual size_t GetStateNesting() const = 0;

		/**
		* Get the top macro nested
		*/
		virtual std::string GetTopMacro() const = 0;
		
		/**
		* Test if the macro pushed is valid
		*/
		virtual bool EvaluateState(std::string line) = 0;
	};
}
