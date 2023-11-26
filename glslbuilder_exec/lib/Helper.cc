#include "Helper.hh"

const std::unordered_map<GLSLBuilder::ArgCategory, std::function<void()>> GLSLBuilderCLI::Helper::s_ArgResolvers =
{
	{
		GLSLBuilder::ArgCategory::HELP, []()
		{
			Console::Log("GLSLBuilder commands:");
			Console::Log("usage: GLSLBuilder version [-v | --version] [-h | --help]");
			Console::Log("[-b/--build]:<build_file_path>(must match a .hls2)");
			Console::Log("[-c/--config]:<build_mode>(Debug/Release: can be either upper or lower case)");
			Console::Log("[-api/--target-api]:<binary_output>(SPV/CSO: can be either upper or lower case)");
			Console::Log("[-h/--help] and [-v/--version], if used, can't receive another arg,\nif used with more args, and exception will be thrown, after detected the second arg");
		}
	},
	{
		GLSLBuilder::ArgCategory::VERSION, []()
		{
			Console::Log("GLSLBuilder version {0}", GLSLBuilder::GLSLBuilderVersion);
		}
	}
};

void GLSLBuilderCLI::Helper::Resolve(GLSLBuilder::ArgCategory category)
{
	auto it = s_ArgResolvers.find(category);
	if (it != s_ArgResolvers.end())
		it->second();
}

void GLSLBuilderCLI::Helper::MultipleInfoError()
{
	Console::Critical("There is more than one info arg passed\n");
	auto it = s_ArgResolvers.find(GLSLBuilder::ArgCategory::HELP);
	if (it != s_ArgResolvers.end())
		it->second();
}

void GLSLBuilderCLI::Helper::InfoControlError()
{
	Console::Critical("Info args passed at same time of control args\n");
	auto it = s_ArgResolvers.find(GLSLBuilder::ArgCategory::HELP);
	if (it != s_ArgResolvers.end())
		it->second();
}