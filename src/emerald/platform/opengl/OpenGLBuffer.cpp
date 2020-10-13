#include "core/empch.h"
#include "platform/opengl/OpenGLBuffer.h"

#include "glad/glad.h"

namespace Emerald {

	//////////////////
	// VertexBuffer //
	//////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		EM_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		EM_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer() 
	{
		EM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}
	
	void OpenGLVertexBuffer::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	
	void OpenGLVertexBuffer::Unbind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////
	// IndexBuffer //
	/////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count) 
	{
		EM_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	
	OpenGLIndexBuffer::~OpenGLIndexBuffer() 
	{
		EM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}
	
	void OpenGLIndexBuffer::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	
	void OpenGLIndexBuffer::Unbind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
}
