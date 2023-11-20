#include <iostream>
#include "Console.hh"
#include <hlslbuilder/CommonExceptions.hh>

int main()
{
	HLSLBuilder::HLSLBuilderException e;
	HLSLBuilderCLI::Console::Init();
	HLSLBuilderCLI::Console::Log("Hello HLSLBuilder");
	HLSLBuilderCLI::Console::Log(e.what());
	HLSLBuilderCLI::Console::End();
	return 0;
}