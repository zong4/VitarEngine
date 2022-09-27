#pragma once

#include "Vitar/Core/Base.h"
#include "Vitar/Core/Log.h"

#include <filesystem>

#ifdef VITAR_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define VITAR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { VITAR##type##ERROR(msg, __VA_ARGS__); VITAR_DEBUGBREAK(); } }
	#define VITAR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) VITAR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define VITAR_INTERNAL_ASSERT_NO_MSG(type, check) VITAR_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", VITAR_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define VITAR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define VITAR_INTERNAL_ASSERT_GET_MACRO(...) VITAR_EXPAND_MACRO( VITAR_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, VITAR_INTERNAL_ASSERT_WITH_MSG, VITAR_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define VITAR_ASSERT(...) VITAR_EXPAND_MACRO( VITAR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define VITAR_CORE_ASSERT(...) VITAR_EXPAND_MACRO( VITAR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define VITAR_ASSERT(...)
	#define VITAR_CORE_ASSERT(...)
#endif
