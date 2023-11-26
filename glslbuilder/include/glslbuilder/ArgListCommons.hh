#pragma once

#include "GLSLBuilderAPI.hh"
#include "CommonExceptions.hh"
#include <exception>
#include <sstream>
#include <unordered_map>

namespace GLSLBuilder
{
	enum class ArgCategory
	{
		BUILD = 0,
		API,
		CONFIG,
		HELP,
		VERSION
	};

	/**
	* ArgException is a base exception that stores the message string and the getter of the message.
	*/
	class GLSLB_API ArgException : public HLSLBuilderException
	{
	};

	/**
	* InvalidArgException is an exception thrown when an unknown arg is pushed.
	*/
	class GLSLB_API InvalidArgException : public ArgException
	{
	public:
		InvalidArgException(std::string_view arg);
	private:
		void BuildInvalidArgString(std::string_view arg);
	};

	/**
	* MismatchArgException is an exception thrown when an info arg is assigned or a control arg is not assigned.
	*/
	class GLSLB_API MismatchArgException : public ArgException
	{
	public:
		MismatchArgException(std::string_view arg, bool controlArg);
	private:
		void BuildMismatchString(std::string_view arg, bool controlArg);
	};

	/**
	* BadAssignmentException is an exception thrown when an arg receives two or more values.
	*/
	class GLSLB_API BadAssignmentException : public ArgException
	{
	public:
		BadAssignmentException(std::string_view message);
	};

	/**
	* BadEvaluationException is an exception thrown when an arg is assigned with an unallowed value.
	*/
	class GLSLB_API BadEvaluationException : public ArgException
	{
	public:
		BadEvaluationException(ArgCategory category, std::string value);
	private:
		void BuildErrorString(ArgCategory category, std::string value);
	};

	/**
	* InvalidUsageException is an exception thrown when a control arg is used beside an info arg.
	*/
	class GLSLB_API InvalidUsageException : public ArgException
	{
	public:
		InvalidUsageException(bool multipleInfoArg);
	private:
		void BuildErrorString(bool multipleInfoArg);
	};

	/**
	* MultipleArgPushException is an exception thrown when an arg is push two or more times.
	*/
	class GLSLB_API MultipleArgPushException : public ArgException
	{
	public:
		MultipleArgPushException(std::string_view argName);
	private:
		void BuildErrorString(std::string_view argName);
	};
}