#include "TextSource.hh"
#include "Utils/FileHandler.hh"
#include <filesystem>
#include "SolutionParser.hh"

const std::unordered_map<GLSLBuilder::ShaderStage, std::string_view> GLSLBuilder::TextSource::s_FileEndpointMapper =
{
	{ ShaderStage::Vertex, "VertexFile" },
	{ ShaderStage::Pixel, "PixelFile" }
};

GLSLBuilder::TextSource::TextSource(std::string_view path)
{
	FileHandler::ReadTextFile(path, &m_SourceCode);
	std::filesystem::path pathName(path.data());
	m_BaseName = pathName.stem().string();
	m_Properties["BaseName"] = m_BaseName;
	m_ParentPath = pathName.parent_path().string();
	std::replace(m_ParentPath.begin(), m_ParentPath.end(), '\\', '/');
}

void GLSLBuilder::TextSource::PreprocessShaders()
{
}

const Json::Value* GLSLBuilder::TextSource::GetProperties() const
{
	return nullptr;
}

void GLSLBuilder::TextSource::ValidateStage(ShaderStage stage, bool present)
{
}

void GLSLBuilder::TextSource::SetCallback(std::function<void(std::string)> callback)
{
}

std::string GLSLBuilder::TextSource::GetBuildPath() const
{
	return std::string();
}
