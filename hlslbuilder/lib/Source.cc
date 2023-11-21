#include "Source.hh"

const std::unordered_map<HLSLBuilder::ShaderStage, std::string_view> HLSLBuilder::Source::s_EntrypointMapper =
{
	{ ShaderStage::Vertex, "VertexEntry" },
	{ ShaderStage::Pixel, "PixelEntry" }
};


