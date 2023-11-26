#pragma once
#include "GLSLBuilderAPI.hh"
#include <string>
#include <utility>

namespace GLSLBuilder
{
	class GLSLB_API FileHandler
	{
	public:
		static bool ReadTextFile(std::string_view path, std::string* content);
		static bool WriteTextFile(std::string_view path, std::string content);
		static bool ReadBinFile(std::string_view path, std::byte** content, size_t* fileSize);
		static bool WriteBinFile(std::string_view path, std::byte* content, size_t dataSize);

		static bool FileExists(std::string_view path);
	};
}