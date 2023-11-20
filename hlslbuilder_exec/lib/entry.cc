#include <iostream>
#include "Console.hh"
#include <hlslbuilder/CommonExceptions.hh>
#include <hlslbuilder/HLSLBuilderVersion.hh>

int main()
{
	HLSLBuilderCLI::Console::Init();
	HLSLBuilderCLI::Console::Log("Hello HLSLBuilder, your version is: {0}", HLSLBuilder::HLSLBuilderVersion);
	HLSLBuilderCLI::Console::End();
	return 0;
}