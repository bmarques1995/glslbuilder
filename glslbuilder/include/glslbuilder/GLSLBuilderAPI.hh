#pragma once

#ifdef GLSLB_WINDOWS
	#ifdef GLSLB_DYNAMIC_LINK
		#ifdef GLSLB_BUILD_DLL
			#define GLSLB_API __declspec(dllexport)
		#else
			#define GLSLB_API __declspec(dllimport)
		#endif
	#else
		#define GLSLB_API
	#endif
#else
	#define GLSLB_API
#endif