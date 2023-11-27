#include "ArgList.hh"
#include "Utils/StringHandler.hh"

#pragma region MappedValues
std::vector<std::string> GLSLBuilder::ArgList::s_StrArgs = std::vector<std::string>();
const std::unordered_map<std::string_view, GLSLBuilder::ArgCategory> GLSLBuilder::ArgList::s_ArgMapper =
{
	{"-b", GLSLBuilder::ArgCategory::BUILD},
	{"--build", GLSLBuilder::ArgCategory::BUILD},
	{"-h", GLSLBuilder::ArgCategory::HELP},
	{"--help", GLSLBuilder::ArgCategory::HELP},
	{"-v", GLSLBuilder::ArgCategory::VERSION},
	{"--version", GLSLBuilder::ArgCategory::VERSION}
};
std::unordered_map<GLSLBuilder::ArgCategory, std::string_view> GLSLBuilder::ArgList::s_ArgValues;

GLSLBuilder::ArgCategory GLSLBuilder::ArgList::s_InfoArg;
bool GLSLBuilder::ArgList::s_InfoAssigned;
std::list<std::pair<GLSLBuilder::ArgCategory, std::string>> GLSLBuilder::ArgList::s_ControlArgTree;

const std::list<GLSLBuilder::ArgCategory> GLSLBuilder::ArgList::s_InfoArgs = std::list<GLSLBuilder::ArgCategory>(
{
	GLSLBuilder::ArgCategory::HELP,
	GLSLBuilder::ArgCategory::VERSION
});
const std::list<GLSLBuilder::ArgCategory> GLSLBuilder::ArgList::s_ControlArgs = std::list<GLSLBuilder::ArgCategory>(
{
	GLSLBuilder::ArgCategory::BUILD
});
#pragma endregion

void GLSLBuilder::ArgList::PushRawArg(std::string_view arg)
{
	std::string parsedArg = arg.data();
	s_StrArgs.push_back(parsedArg);
}

void GLSLBuilder::ArgList::ResolveArgs()
{
	for (auto& i : s_StrArgs)
	{
		ClassifyAndEvaluateArgs(i);
	}
	//validate usage
}

void GLSLBuilder::ArgList::ClearArgs()
{
	s_StrArgs.clear();
	s_InfoAssigned = false;
	while (s_ControlArgTree.size() > 0)
		s_ControlArgTree.pop_front();
}

GLSLBuilder::ArgCategory GLSLBuilder::ArgList::GetInfoArg()
{
	return s_InfoArg;
}

std::list<std::pair<GLSLBuilder::ArgCategory, std::string>> GLSLBuilder::ArgList::GetControlArgs()
{
	return s_ControlArgTree;
}

void GLSLBuilder::ArgList::ClassifyAndEvaluateArgs(std::string_view arg)
{
	std::string text = arg.data();

	std::regex pattern(":");

	std::sregex_token_iterator matcher(text.begin(), text.end(), pattern, -1);
	std::sregex_token_iterator end;

	size_t numOfMatches = std::distance(matcher, end) - 1;

	if (numOfMatches > 1)
	{
		throw BadAssignmentException("Invalid Argument Assigment Evaluation, neither argument accept two values");
	}

	if (numOfMatches == 0)
		PushInfoArgTreated(text);
	else
		PushControlArgTreated(&matcher);

}

void GLSLBuilder::ArgList::PushInfoArgTreated(std::string_view arg)
{
	std::string treatedArg = arg.data();
	StringHandler::ToLower(&treatedArg);
	auto it = s_ArgMapper.find(treatedArg);
	if (it != s_ArgMapper.end())
	{
		//multiple push treatment
		if (s_ControlArgTree.size() > 0)
			throw InvalidUsageException(false);
		if (s_InfoAssigned)
			throw InvalidUsageException(true);
		auto list_it = std::find(s_InfoArgs.begin(), s_InfoArgs.end(), it->second);
		if (list_it == s_InfoArgs.end())
			throw MismatchArgException(arg, true);
		else
		{
			s_InfoAssigned = true;
			s_InfoArg = it->second;
		}
	}
	else
		throw InvalidArgException(arg);
}

void GLSLBuilder::ArgList::PushControlArgTreated(std::sregex_token_iterator* arg)
{
	std::sregex_token_iterator end;
	size_t elementsCount = (*arg)->length();
	std::string* args = new std::string[elementsCount];
	size_t i = 0;
	while ((*arg) != end)
	{
		args[i] = (*arg)->str();
		++(*arg);
		++i;
	}
	std::string treatedArg = args[0];
	StringHandler::ToLower(&treatedArg);
	std::string treatedValue = args[1];
	delete[] args;
	auto it = s_ArgMapper.find(treatedArg);
	if (it != s_ArgMapper.end())
	{
		if(it->second != ArgCategory::BUILD)
			StringHandler::ToLower(&treatedValue);
		if (s_InfoAssigned)
			throw InvalidUsageException(false);
		if (ArgumentPushed(it->second))
			throw MultipleArgPushException(treatedArg);
		auto list_it = std::find(s_ControlArgs.begin(), s_ControlArgs.end(), it->second);
		if (list_it == s_ControlArgs.end())
			throw MismatchArgException(treatedArg, false);
		else
		{
			s_ControlArgTree.push_back(std::make_pair(it->second, treatedValue));
		}
	}
	else
		throw InvalidArgException(treatedArg);
	
}

bool GLSLBuilder::ArgList::ArgumentPushed(ArgCategory category)
{
	bool found = false;
	for (auto it = s_ControlArgTree.begin(); it != s_ControlArgTree.end(); it++)
	{
		auto value = *it;
		if (value.first == category)
		{
			found = true;
			break;
		}
	}
	return found;
}
