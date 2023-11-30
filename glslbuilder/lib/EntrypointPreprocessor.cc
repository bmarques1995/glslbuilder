#include "EntrypointPreprocessor.hh"
#include "BuilderCommons.hh"

GLSLBuilder::EntrypointPreprocessor::EntrypointPreprocessor() :
	m_PushRequest("(#push_entrypoint)\\((\\w+)\\)|#pop_entrypoint"), m_PushValidation("^(#push_entrypoint)\\((\\w+)\\)$|^#pop_entrypoint$"),
	m_NameValidation("^[a-zA-Z_][a-zA-Z0-9_]*$")
{
}

size_t GLSLBuilder::EntrypointPreprocessor::GetStateNesting() const
{
	return m_MacroStack.size();
}

std::string GLSLBuilder::EntrypointPreprocessor::GetTopMacro() const
{
	return m_MacroStack.top();
}

bool GLSLBuilder::EntrypointPreprocessor::EvaluateState(std::string line)
{
	std::smatch requestMatch;
	std::string name, value;

	if (!std::regex_search(line, requestMatch, m_PushRequest))
		return false;
	else
	{
		ValidateMacro(line);
		if (requestMatch[1].length() == 0)
			name = requestMatch[0];
		else
			name = requestMatch[1];
		value = requestMatch[2];
		if (name.compare("#push_entrypoint") == 0)
		{
			ValidateValue(value);
			if (m_MacroStack.size() > 0)
				throw MultipleEntrypointNestingException();
			m_MacroStack.push(value);
		}
		else
			m_MacroStack.pop();
		return true;
	}
}

void GLSLBuilder::EntrypointPreprocessor::ValidateMacro(std::string_view value)
{
	std::string line = value.data();
	std::smatch validationMatch;

	if (!std::regex_search(line, validationMatch, m_PushValidation))
		throw EntrypointPreprocessorAssigmentException(value.data());
}

void GLSLBuilder::EntrypointPreprocessor::ValidateValue(std::string_view value)
{
	std::string line = value.data();
	std::smatch validationMatch;

	if (!std::regex_search(line, validationMatch, m_NameValidation))
		throw NameEvaluationException(value.data());
}
