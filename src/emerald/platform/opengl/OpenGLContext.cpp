#include "core/empch.h"
#include "platform/opengl/OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Emerald {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EM_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		EM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		GLint texture_units;
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texture_units);
		EM_CORE_ASSERT(status, "Failed to initialize glad!");

		EM_CORE_INFO("OpenGL Info:");
		EM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		EM_CORE_INFO("  Maximum bound texture units: {0}", texture_units);
		
		EM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Emerald requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		EM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
