#include "Helper.hh"

const std::unordered_map<HLSLBuilder::ArgCategory, std::function<void()>> HLSLBuilderCLI::Helper::s_ArgResolvers =
{
	{
		HLSLBuilder::ArgCategory::HELP, []()
		{
			Console::Log("HLSLBuilder commands:");
			Console::Log("usage: HLSLBuilder version [-v | --version] [-h | --help]");
			Console::Log("[-b/--build]:<build_file_path>(must match a .hls2)");
			Console::Log("[-c/--config]:<build_mode>(Debug/Release: can be either upper or lower case)");
			Console::Log("[-api/--target-api]:<binary_output>(SPV/CSO: can be either upper or lower case)");
			Console::Log("[-h/--help] and [-v/--version], if used, can't receive another arg,\nif used with more args, and exception will be thrown, after detected the second arg");
		}
	},
	{
		HLSLBuilder::ArgCategory::VERSION, []()
		{
			Console::Log("HLSLBuilder version {0}", HLSLBuilder::HLSLBuilderVersion);
		}
	}
};

void HLSLBuilderCLI::Helper::Resolve(HLSLBuilder::ArgCategory category)
{
	auto it = s_ArgResolvers.find(category);
	if (it != s_ArgResolvers.end())
		it->second();
}

void HLSLBuilderCLI::Helper::MultipleInfoError()
{
	Console::Critical("There is more than one info arg passed\n");
	auto it = s_ArgResolvers.find(HLSLBuilder::ArgCategory::HELP);
	if (it != s_ArgResolvers.end())
		it->second();
}

void HLSLBuilderCLI::Helper::InfoControlError()
{
	Console::Critical("Info args passed at same time of control args\n");
	auto it = s_ArgResolvers.find(HLSLBuilder::ArgCategory::HELP);
	if (it != s_ArgResolvers.end())
		it->second();
}