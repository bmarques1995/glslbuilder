#include "Builder.hh"
#include <sstream>
#include <filesystem>
#include <regex>
#include "Utils/FileHandler.hh"
#include "SolutionParser.hh"

//std::list<GLSLBuilder::GraphicsSource> GLSLBuilder::Builder::s_GraphicsSources;
GLSLBuilder::Version GLSLBuilder::Builder::s_HLSLVersion;
GLSLBuilder::Version GLSLBuilder::Builder::s_VulkanVersion;
GLSLBuilder::BuildMode GLSLBuilder::Builder::s_BuildMode;
GLSLBuilder::OutputTarget GLSLBuilder::Builder::s_OutputTarget;
Json::Value GLSLBuilder::Builder::s_Output;
std::function<void(std::string)> GLSLBuilder::Builder::s_Callback = [](std::string value){};

void GLSLBuilder::Builder::SetBuildArgs(Json::Value& solution, BuildMode buildMode, OutputTarget outputTarget)
{
	
}

void GLSLBuilder::Builder::BuildSources()
{
	
}

void GLSLBuilder::Builder::Clear()
{
	//s_GraphicsSources.clear();
}

void GLSLBuilder::Builder::SetCallback(std::function<void(std::string)> callback)
{
	s_Callback = callback;
	/*for (auto& i : s_GraphicsSources)
	{
		i.SetCallback(callback);
	}*/
}

void GLSLBuilder::Builder::SendBuildMessage(const Source& source)
{
	std::stringstream buffer;
	buffer << "Building file: " << source.GetBuildPath();
	s_Callback(buffer.str());
}

void GLSLBuilder::Builder::ValidateGLSLVersion()
{
	
}

void GLSLBuilder::Builder::ValidateVulkanVersion()
{
	
}

void GLSLBuilder::Builder::ValidateOutputTarget()
{
	
}
