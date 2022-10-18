#pragma once

#include "glm/gtx/string_cast.hpp"

#include "Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#pragma warning(pop)

namespace Vitar
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternio)
{
	return os << glm::to_string(quaternio);
}

// Core log macros
#define VITAR_CORE_TRACE(...)     ::Vitar::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VITAR_CORE_INFO(...)      ::Vitar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VITAR_CORE_WARN(...)      ::Vitar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VITAR_CORE_ERROR(...)     ::Vitar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VITAR_CORE_CRITICAL(...)  ::Vitar::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VITAR_TRACE(...)          ::Vitar::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VITAR_INFO(...)           ::Vitar::Log::GetClientLogger()->info(__VA_ARGS__)
#define VITAR_WARN(...)           ::Vitar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VITAR_ERROR(...)          ::Vitar::Log::GetClientLogger()->error(__VA_ARGS__)
#define VITAR_CRITICAL(...)       ::Vitar::Log::GetClientLogger()->critical(__VA_ARGS__)

