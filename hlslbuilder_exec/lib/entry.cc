#include <iostream>
#include "Console.hh"

int main()
{
	HLSLBuilderCLI::Console::Init();
	HLSLBuilderCLI::Console::Log("Hello HLSLBuilder");
	HLSLBuilderCLI::Console::End();
	return 0;
}