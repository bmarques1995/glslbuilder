#include <iostream>
#include "Console.hh"
#include "Helper.hh"
#include <hlslbuilder/CommonExceptions.hh>
#include <hlslbuilder/HLSLBuilder.hh>

int main(int argc, char** argv)
{
	HLSLBuilderCLI::Console::Init();
	HLSLBuilderCLI::Console::Log("Hello HLSLBuilder, your version is: {0}", HLSLBuilder::HLSLBuilderVersion);
	for (size_t i = 1; i < argc; i++)
	{
		HLSLBuilder::ArgList::PushRawArg(argv[i]);
	}
	try
	{
		HLSLBuilder::ArgList::ResolveArgs();
	}
	catch (HLSLBuilder::ArgException e)
	{
		HLSLBuilderCLI::Console::Critical("{0}\n", e.what());
		HLSLBuilderCLI::Helper::Resolve(HLSLBuilder::ArgCategory::HELP);
		exit(2);
	}
	HLSLBuilderCLI::Console::End();
	return 0;
}