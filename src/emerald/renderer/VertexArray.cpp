#include "core/empch.h"
#include "renderer/VertexArray.h"

#include "renderer/Renderer.h"
#include "platform/opengl/OpenGLVertexArray.h"

namespace Emerald {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
