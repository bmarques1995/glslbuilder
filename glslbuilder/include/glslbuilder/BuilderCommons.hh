#pragma once

#include <string>
#include <exception>
#include "CommonExceptions.hh"

namespace GLSLBuilder
{

	/**
	* Base class of preprocessor exceptions
	*/
	class GLSLB_API PreprocessorException : public GLSLBuilderException
	{
	};

	/**
	* Exception thrown when the macro is invalidly assigned.
	*/
	class GLSLB_API EntrypointPreprocessorAssigmentException : public PreprocessorException
	{
	public:
		EntrypointPreprocessorAssigmentException(std::string line);
	};

	/**
	* Exception thrown when the arg is invalid.
	*/
	class GLSLB_API NameEvaluationException : public PreprocessorException
	{
	public:
		NameEvaluationException(std::string name);
	};

	/**
	* Exception thrown when multiple entrypoint are tried to push.
	*/
	class GLSLB_API MultipleEntrypointNestingException : public PreprocessorException
	{
	public:
		MultipleEntrypointNestingException();
	};

	/**
	* Exception thrown when #pop_entrypoint is not called.
	*/
	class GLSLB_API MissingEntrypointPoppingException : public PreprocessorException
	{
	public:
		MissingEntrypointPoppingException();
	};
}