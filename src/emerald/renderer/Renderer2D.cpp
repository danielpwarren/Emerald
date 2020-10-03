#include "core/empch.h"
#include "Renderer2D.h"

#include "renderer/RenderCommand.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

#include "platform/opengl/OpenGLShader.h"

namespace Emerald {

	struct Renderer2DData
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> flatColorShader;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData;

		s_Data->vertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		s_Data->vertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->vertexArray->SetIndexBuffer(squareIndexBuffer);

		s_Data->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color)
	{
		DrawQuad(glm::vec3(position, 1.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(s_Data->flatColorShader)->UploadUniformFloat4("u_Color", color);

		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

}