#pragma once

#include "Preprocessor.hh"
#include <stack>
#include <regex>

namespace GLSLBuilder
{
	/**
	* This class preprocesses the macro `#push_entrypoint`
	*/
	class EntrypointPreprocessor : public Preprocessor
	{
	public:
		/**
		* Starts the entrypoint stack
		*/
		EntrypointPreprocessor();
		virtual ~EntrypointPreprocessor() = default;

		/**
		* Get the number of pushed macro nested
		*/
		size_t GetStateNesting() const override;

		/**
		* Get the top macro nested
		*/
		std::string GetTopMacro() const override;
		
		/**
		* Test if the macro pushed is valid
		*/
		bool EvaluateState(std::string line) override;
		
	private:

		void ValidateMacro(std::string_view value);
		void ValidateValue(std::string_view value);

		std::stack<std::string> m_MacroStack;
		std::regex m_PushRequest;
		std::regex m_PushValidation;
		std::regex m_NameValidation;
	};
}