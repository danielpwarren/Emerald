#pragma once

#include <memory>

#include "core/PlatformDetection.h"

#ifdef EM_DEBUG
#define EM_PROFILE
	#define EM_ASSERT(x, ...) { if(!(x)) { EM_ERROR("Assertion Failed: {0}", __VA_ARGS__); EM_DEBUG_BREAK(); } }
	#define EM_CORE_ASSERT(x, ...) { if(!(x)) { EM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); EM_DEBUG_BREAK(); } }
	#if defined(EM_PLATFORM_LINUX) || defined(EM_PLATFORM_MACOS)
		#include <signal.h>
		#define EM_DEBUG_BREAK() raise(SIGTRAP)
	#elif defined(EM_PLATFORM_WINDOWS)
		#define EM_DEBUG_BREAK() __debugbreak()
	#endif
#else
	#define EM_DEBUG_BREAK()
	#define EM_ASSERT(x, ...)
	#define EM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))

#define EM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Emerald {

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
