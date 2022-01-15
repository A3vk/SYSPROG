#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#ifdef RANDOMLIB_EXPORTS
		#define DLL_EXPORT __declspec(dllexport)
	#else
		#define DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#error Platform not supported
#endif