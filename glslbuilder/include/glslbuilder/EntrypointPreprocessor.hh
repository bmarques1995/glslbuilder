#pragma once

#include "Preprocessor.hh"
#include <stack>
#include <regex>

namespace GLSLBuilder
{
	class EntrypointPreprocessor : public Preprocessor
	{
	public:
		EntrypointPreprocessor();
		virtual ~EntrypointPreprocessor() = default;

		size_t GetStateNesting() const override;
		std::string GetTopMacro() const override;
		
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