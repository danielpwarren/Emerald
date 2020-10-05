#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Emerald {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define EM_CORE_TRACE(...) 		::Emerald::Log::getCoreLogger()->trace(__VA_ARGS__)
#define EM_CORE_INFO(...) 		::Emerald::Log::getCoreLogger()->info(__VA_ARGS__)
#define EM_CORE_WARN(...) 		::Emerald::Log::getCoreLogger()->warn(__VA_ARGS__)
#define EM_CORE_ERROR(...) 		::Emerald::Log::getCoreLogger()->error(__VA_ARGS__)
#define EM_CORE_CRITICAL(...) 	::Emerald::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EM_TRACE(...) 		::Emerald::Log::getClientLogger()->trace(__VA_ARGS__)
#define EM_INFO(...) 		::Emerald::Log::getClientLogger()->info(__VA_ARGS__)
#define EM_WARN(...) 		::Emerald::Log::getClientLogger()->warn(__VA_ARGS__)
#define EM_ERROR(...) 		::Emerald::Log::getClientLogger()->error(__VA_ARGS__)
#define EM_CRITICAL(...) 	::Emerald::Log:getClientLogger()->critical(__VA_ARGS__)
