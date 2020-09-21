#include "core/empch.h"
#include "platform/opengl/OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Emerald {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EM_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EM_CORE_ASSERT(status, "Failed to initialize glad!");

		EM_CORE_INFO("OpenGL Info:");
		EM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		
		EM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
