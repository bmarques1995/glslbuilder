#include "Source.hh"

const std::unordered_map<GLSLBuilder::ShaderStage, std::string_view> GLSLBuilder::Source::s_EntrypointMapper =
{
	{ ShaderStage::Vertex, "VertexEntry" },
	{ ShaderStage::Pixel, "PixelEntry" }
};
