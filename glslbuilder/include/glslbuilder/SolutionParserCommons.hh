#pragma once

#include "CommonExceptions.hh"

namespace GLSLBuilder
{
	enum class PropertyType
	{
		NAME = 0,
		PATH_ARRAY,
		VERSION
	};

	class GLSLB_API PropertyException : public HLSLBuilderException
	{
	};

	/**
	* PropertyNotFoundException is an exception thrown when a mandatory property is missing.
	*
	* More details can be found in [HLS2](@ref docs/hls2.md).
	*/
	class GLSLB_API PropertyNotFoundException : public PropertyException
	{
	public:
		PropertyNotFoundException(std::string_view property);
	};

	/**
	* InvalidVersionException is an exception thrown when there is a mismatch in a version argument.
	*
	* More details can be found in [HLS2](@ref docs/hls2.md).
	*/
	class GLSLB_API InvalidVersionException : public PropertyException
	{
	public:
		InvalidVersionException(std::string_view arg);
	};

	/**
	* InvalidNameException is an exception thrown when there is a mismatch in a name argument.
	*
	* More details can be found in [HLS2](@ref docs/hls2.md).
	*/
	class GLSLB_API InvalidNameException : public PropertyException
	{
	public:
		InvalidNameException(std::string_view arg);
	};

	/**
	* SourceNotFoundException is an exception thrown when a source path is not found.
	*
	* More details can be found in [HLS2](@ref docs/hls2.md).
	*/
	class GLSLB_API SourceNotFoundException : public PropertyException
	{
	public:
		SourceNotFoundException(std::string_view arg);
	};

	/**
	* InvalidSourceArrayException is an exception thrown when there is a mismatch in a path array argument.
	*
	* More details can be found in [HLS2](@ref docs/hls2.md).
	*/
	class GLSLB_API InvalidArrayException : public PropertyException
	{
	public:
		InvalidArrayException();
	};
}