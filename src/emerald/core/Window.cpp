#include "core/empch.h"
#include "core/Window.h"

#if defined(EM_PLATFORM_WINDOWS)
#include "platform/windows/WindowsWindow.h"
#elif defined(EM_PLATFORM_LINUX)
#include "platform/linux/LinuxWindow.h"
#elif defined(EM_PLATFORM_MACOS)
#include "platform/macos/MacOSWindow.h"
#endif

namespace Emerald {

	Scope<Window> Window::Create(const WindowProps& props)
	{
	#if defined(EM_PLATFORM_WINDOWS)
		return CreateScope<WindowsWindow>(props);
	#elif defined(EM_PLATFORM_LINUX)
		return CreateScope<LinuxWindow>(props);
	#elif defined(EM_PLATFORM_MACOS)
		return CreateScope<MacOSWindow>(props);
	#else
		EM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}