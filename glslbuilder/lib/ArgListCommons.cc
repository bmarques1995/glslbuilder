#include "ArgListCommons.hh"

GLSLBuilder::BadEvaluationException::BadEvaluationException(ArgCategory category, std::string value)
{
	BuildErrorString(category, value);
}

void GLSLBuilder::BadEvaluationException::BuildErrorString(ArgCategory category, std::string value)
{
	const std::unordered_map<ArgCategory, std::string> categoryCast =
	{
		{GLSLBuilder::ArgCategory::API, "-api"},
		{GLSLBuilder::ArgCategory::API, "--target-api"},
		{GLSLBuilder::ArgCategory::CONFIG, "-c"},
		{GLSLBuilder::ArgCategory::CONFIG, "--config"}
	};

	std::stringstream error;
	error << "Invalid assignment to: ";
	auto category_it = categoryCast.find(category);
	if (category_it != categoryCast.end())
		error << category_it->second;
	error << ", the value <" << value << "> isn't allowed";
	m_Exception = error.str();
}

GLSLBuilder::InvalidArgException::InvalidArgException(std::string_view arg)
{
	BuildInvalidArgString(arg);
}

void GLSLBuilder::InvalidArgException::BuildInvalidArgString(std::string_view arg)
{
	std::stringstream messageBuffer;
	messageBuffer << "Argument: " << arg << " not found";
	m_Exception = messageBuffer.str();
}

GLSLBuilder::MismatchArgException::MismatchArgException(std::string_view arg, bool controlArg)
{
	BuildMismatchString(arg, controlArg);
}

void GLSLBuilder::MismatchArgException::BuildMismatchString(std::string_view arg, bool controlArg)
{
	std::stringstream messageBuffer;
	messageBuffer << "Invalid Argument Assigment\nArgument: " << arg;
	if (controlArg)
		messageBuffer << " is a control arg, so must be assigned";
	else
		messageBuffer << " isn't a control arg, so is unassigned";
	m_Exception = messageBuffer.str();
}

GLSLBuilder::BadAssignmentException::BadAssignmentException(std::string_view message)
{
	m_Exception = message.data();
}

GLSLBuilder::InvalidUsageException::InvalidUsageException(bool multipleInfoArg)
{
	BuildErrorString(multipleInfoArg);
}

void GLSLBuilder::InvalidUsageException::BuildErrorString(bool multipleInfoArg)
{
	m_Exception = multipleInfoArg ? "Unable to use multiple info arguments" : "Info arguments are not allowed using control args";
}

GLSLBuilder::MultipleArgPushException::MultipleArgPushException(std::string_view argName)
{
	BuildErrorString(argName);
}

void GLSLBuilder::MultipleArgPushException::BuildErrorString(std::string_view argName)
{
	std::stringstream messageBuffer;
	messageBuffer << "Argument: \"" << argName.data() << "\" insert twice.";
	m_Exception = messageBuffer.str();
}