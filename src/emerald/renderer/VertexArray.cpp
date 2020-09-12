#include "core/em.pch"
#include "renderer/VertexArray.h"

#include "renderer/Renderer.h" 
#include "platform/opengl/OpenGLVertexArray.h"

namespace Emerald {

	VertexArray* VertexArray::Create() 
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr; 
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		EM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
