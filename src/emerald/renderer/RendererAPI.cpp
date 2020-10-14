#include "core/empch.h"
#include "renderer/RendererAPI.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Emerald {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:    EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
