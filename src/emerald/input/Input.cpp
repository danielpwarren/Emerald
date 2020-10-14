#include "core/empch.h"
#include "input/Input.h"

#if defined(EM_PLATFORM_WINDOWS)
#include "platform/windows/WindowsInput.h"
#elif defined(EM_PLATFORM_LINUX)
#include "platform/linux/LinuxInput.h"
#elif defined(EM_PLATFORM_MACOS)
#include "platform/macos/MacOSInput.h"
#endif

namespace Emerald {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#if defined(EM_PLATFORM_WINDOWS)
		return CreateScope<WindowsInput>();
	#elif defined(EM_PLATFORM_LINUX)
		return CreateScope<LinuxInput>();
	#elif defined(EM_PLATFORM_MACOS)
		return CreateScope<MacOSInput>();
	#else
		EM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}