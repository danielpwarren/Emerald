#pragma once

#include "core/Base.h"

#include "spdlog/spdlog.h"


namespace Emerald {
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define EM_CORE_TRACE(...) 		::Emerald::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EM_CORE_INFO(...) 		::Emerald::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EM_CORE_WARN(...) 		::Emerald::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EM_CORE_ERROR(...) 		::Emerald::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EM_CORE_CRITICAL(...) 	::Emerald::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EM_TRACE(...) 		::Emerald::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EM_INFO(...) 		::Emerald::Log::GetClientLogger()->info(__VA_ARGS__)
#define EM_WARN(...) 		::Emerald::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EM_ERROR(...) 		::Emerald::Log::GetClientLogger()->error(__VA_ARGS__)
#define EM_CRITICAL(...) 	::Emerald::Log::GetClientLogger()->critical(__VA_ARGS__)
