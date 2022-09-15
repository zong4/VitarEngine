#pragma once

#ifdef VITAR_PLANTFORM_WINDOWS
	#ifdef VITAR_BUILD_DLL
		#define VITAR_API __declspec(dllexport)
	#else
		#define VITAR_API __declspec(dllimport)
	#endif // VITAR_BUILD_DLL
#else
	#error Vitar only supports Windows!
#endif // VITAR_PLANTFORM_WINDOWS
