#pragma once

#ifdef EM_PLATFORM_WINDOWS
	#ifdef EM_BUILD_DLL
		#define EM_API __declspec(dllexport)
	#else
		#define EM_API __declspec(dllimport)
	#endif
	#define EM_DEBUG_BREAK() __debugbreak()
#else
	#define EM_API
#endif

#ifdef EM_PLATFORM_LINUX
	#include <signal.h>
	#define EM_DEBUG_BREAK() raise(SIGTRAP)
#endif

#ifndef EM_DEBUG_BREAK()
	#define EM_DEBUG_BREAK()
#endif

#ifdef EM_DEBUG
	#define EM_ENABLE_ASSERTS
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