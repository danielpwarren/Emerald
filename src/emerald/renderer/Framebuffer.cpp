#include "core/empch.h"
#include "renderer/Framebuffer.h"

#include "renderer/Renderer.h"

#include "platform/opengl/OpenGLFramebuffer.h"

namespace Emerald {


	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(specification);
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
}