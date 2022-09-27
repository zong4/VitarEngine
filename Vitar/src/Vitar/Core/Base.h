#pragma once

#include <memory>

#include "PlatformDetection.h"

#ifdef VITAR_DEBUG
	#if defined(VITAR_PLATFORM_WINDOWS)
		#define VITAR_DEBUGBREAK() __debugbreak()
	#elif defined(VITAR_PLATFORM_LINUX)
		#include <signal.h>
		#define VITAR_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#define VITAR_ENABLE_ASSERTS
#else
	#define VITAR_DEBUGBREAK()
#endif

#define VITAR_EXPAND_MACRO(x) x
#define VITAR_STRINGIFY_MACRO(x) #x


#define BIT(x) (1 << x)

#define VITAR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Vitar
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Vitar/Core/Log.h"
#include "Vitar/Core/Assert.h"
