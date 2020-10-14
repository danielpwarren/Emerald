#include "core/empch.h"
#include "renderer/GraphicsContext.h"

#include "renderer/Renderer.h"
#include "platform/opengl/OpenGLContext.h"

namespace Emerald {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}