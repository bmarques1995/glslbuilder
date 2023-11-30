#include "BuilderCommons.hh"
#include <sstream>

GLSLBuilder::EntrypointPreprocessorAssigmentException::EntrypointPreprocessorAssigmentException(std::string line)
{
	std::stringstream buffer;
	buffer << "Error on \"" << line << "\" assigment\n";
	buffer << "you must assign with \n\n`#push_entrypoint(<value>)`\n\n or \n\n`#pop_entrypoint`\n\nAnd nothing more on the lines where push or pop is assigned, even spaces, tabs or any other char different from the new line\n";
	buffer << "The chars `` represents a code snippet";
	m_Exception = buffer.str();
}

GLSLBuilder::NameEvaluationException::NameEvaluationException(std::string name)
{
	std::stringstream buffer;
	buffer << "Error on name:\"" << name << "\" assigment\n";
	buffer << "names must start with a letter or \'_\' and can only be followed by other letters, digits or \'_\'";
	m_Exception = buffer.str();
}

GLSLBuilder::MultipleEntrypointNestingException::MultipleEntrypointNestingException()
{
	m_Exception = "There can be only 1 entrypoint active,\nif you want to treat another entrypoint, you must `#pop_entrypoint` the current entrypoint";
}

GLSLBuilder::MissingEntrypointPoppingException::MissingEntrypointPoppingException()
{
	m_Exception = "All `#push_entrypoint` instance must be popped, with `#pop_entrypoint`";
}
