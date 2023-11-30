#pragma once

#include <string>
#include <exception>
#include "CommonExceptions.hh"

namespace GLSLBuilder
{
	class GLSLB_API PreprocessorException : public GLSLBuilderException
	{
	};

	class GLSLB_API EntrypointPreprocessorAssigmentException : public PreprocessorException
	{
	public:
		EntrypointPreprocessorAssigmentException(std::string line);
	};

	class GLSLB_API NameEvaluationException : public PreprocessorException
	{
	public:
		NameEvaluationException(std::string name);
	};

	class GLSLB_API MultipleEntrypointNestingException : public PreprocessorException
	{
	public:
		MultipleEntrypointNestingException();
	};

	class GLSLB_API MissingEntrypointPoppingException : public PreprocessorException
	{
	public:
		MissingEntrypointPoppingException();
	};
}