#include "core/empch.h"
#include "renderer/Buffer.h"

#include "renderer/Renderer.h"

#include "platform/opengl/OpenGLBuffer.h"

namespace Emerald {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr; 
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        EM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: EM_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr; 
            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(vertices, size);
        }

        EM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
