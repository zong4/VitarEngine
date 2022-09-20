#pragma once

#ifdef VITAR_PLANTFORM_WINDOWS
#if VITAR_DYNAMIC_LINK
	#ifdef VITAR_BUILD_DLL
		#define VITAR_API __declspec(dllexport)
	#else
		#define VITAR_API __declspec(dllimport)
	#endif // VITAR_BUILD_DLL
#else
	#define VITAR_API
#endif
#else
	#error Vitar only supports Windows!
#endif // VITAR_PLANTFORM_WINDOWS


//#define VITAR_ENABLE_ASSERTS 0

#ifdef VITAR_DEBUG
	#define VITAR_ENABLE_ASSERTS
#endif // VITAR_DEBUG

#ifdef VITAR_ENABLE_ASSERTS
	#define VITAR_ASSERT(x, ...){ if(!(x)) { VITAR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VITAR_CORE_ASSERT(x, ...){ if(!(x)) { VITAR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VITAR_ASSERT(x, ...)
	#define VITAR_CORE_ASSERT(x, ...)
#endif // VITAR_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define VITAR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
