#pragma once

#ifdef EM_DEBUG
	#define EM_ENABLE_ASSERTS
	#if defined(EM_PLATFORM_LINUX)
		#include <signal.h>
		#define EM_DEBUG_BREAK() raise(SIGTRAP)
	#elif defined(EM_PLATFORM_WINDOWS)
		#define EM_DEBUG_BREAK() __debugbreak()
	#endif
#else
	#define EM_DEBUG_BREAK()
#endif

#ifdef EM_ENABLE_ASSERTS
	#define EM_ASSERT(x, ...) { if(!(x)) { EM_ERROR("Assertion Failed: {0}", __VA_ARGS__); EM_DEBUG_BREAK(); } }
	#define EM_CORE_ASSERT(x, ...) { if(!(x)) { EM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); EM_DEBUG_BREAK(); } }
#else
	#define EM_ASSERT(x, ...)
	#define EM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define EM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)