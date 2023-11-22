#include "ArgList.hh"
#include "Utils/StringHandler.hh"

#pragma region MappedValues
std::vector<std::string> HLSLBuilder::ArgList::s_StrArgs = std::vector<std::string>();
const std::unordered_map<std::string_view, HLSLBuilder::ArgCategory> HLSLBuilder::ArgList::s_ArgMapper =
{
	{"-api", HLSLBuilder::ArgCategory::API},
	{"--target-api", HLSLBuilder::ArgCategory::API},
	{"-b", HLSLBuilder::ArgCategory::BUILD},
	{"--build", HLSLBuilder::ArgCategory::BUILD},
	{"-c", HLSLBuilder::ArgCategory::CONFIG},
	{"--config", HLSLBuilder::ArgCategory::CONFIG},
	{"-h", HLSLBuilder::ArgCategory::HELP},
	{"--help", HLSLBuilder::ArgCategory::HELP},
	{"-v", HLSLBuilder::ArgCategory::VERSION},
	{"--version", HLSLBuilder::ArgCategory::VERSION}
};
std::unordered_map<HLSLBuilder::ArgCategory, std::string_view> HLSLBuilder::ArgList::s_ArgValues;

const std::unordered_map<std::string_view, HLSLBuilder::ArgCategory> HLSLBuilder::ArgList::s_ValidAssignments =
{
	{"cso", HLSLBuilder::ArgCategory::API},
	{"spv", HLSLBuilder::ArgCategory::API},
	{"debug", HLSLBuilder::ArgCategory::CONFIG},
	{"release", HLSLBuilder::ArgCategory::CONFIG}
};

HLSLBuilder::ArgCategory HLSLBuilder::ArgList::s_InfoArg;
bool HLSLBuilder::ArgList::s_InfoAssigned;
std::list<std::pair<HLSLBuilder::ArgCategory, std::string>> HLSLBuilder::ArgList::s_ControlArgTree;

const std::list<HLSLBuilder::ArgCategory> HLSLBuilder::ArgList::s_InfoArgs = std::list<HLSLBuilder::ArgCategory>(
{
	HLSLBuilder::ArgCategory::HELP,
	HLSLBuilder::ArgCategory::VERSION
});
const std::list<HLSLBuilder::ArgCategory> HLSLBuilder::ArgList::s_ControlArgs = std::list<HLSLBuilder::ArgCategory>(
{
	HLSLBuilder::ArgCategory::API,
	HLSLBuilder::ArgCategory::BUILD,
	HLSLBuilder::ArgCategory::CONFIG
});
#pragma endregion

void HLSLBuilder::ArgList::PushRawArg(std::string_view arg)
{
	std::string parsedArg = arg.data();
	s_StrArgs.push_back(parsedArg);
}

void HLSLBuilder::ArgList::ResolveArgs()
{
	for (auto& i : s_StrArgs)
	{
		ClassifyAndEvaluateArgs(i);
	}
	//validate usage
}

void HLSLBuilder::ArgList::ClearArgs()
{
	s_StrArgs.clear();
	s_InfoAssigned = false;
	while (s_ControlArgTree.size() > 0)
		s_ControlArgTree.pop_front();
}

HLSLBuilder::ArgCategory HLSLBuilder::ArgList::GetInfoArg()
{
	return s_InfoArg;
}

std::list<std::pair<HLSLBuilder::ArgCategory, std::string>> HLSLBuilder::ArgList::GetControlArgs()
{
	return s_ControlArgTree;
}

void HLSLBuilder::ArgList::ClassifyAndEvaluateArgs(std::string_view arg)
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

void HLSLBuilder::ArgList::ValidateControlAssignment(std::string_view value, HLSLBuilder::ArgCategory category)
{
	if (category == ArgCategory::BUILD)
		return;
	auto list_it = s_ValidAssignments.find(value);
	if ((list_it == s_ValidAssignments.end()) || (list_it->second != category))
		throw BadEvaluationException(category, value.data());
}

void HLSLBuilder::ArgList::PushInfoArgTreated(std::string_view arg)
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

void HLSLBuilder::ArgList::PushControlArgTreated(std::sregex_token_iterator* arg)
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
			ValidateControlAssignment(treatedValue, it->second);
			s_ControlArgTree.push_back(std::make_pair(it->second, treatedValue));
		}
	}
	else
		throw InvalidArgException(treatedArg);
	
}

bool HLSLBuilder::ArgList::ArgumentPushed(ArgCategory category)
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
