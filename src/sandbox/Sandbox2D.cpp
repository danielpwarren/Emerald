#include "Sandbox2D.h"
#include "platform/opengl/OpenGLShader.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Emerald::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Emerald::Ref<Emerald::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = Emerald::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVertexBuffer->SetLayout({
		{ Emerald::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Emerald::Ref<Emerald::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer = Emerald::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = Emerald::Shader::Create("assets/shaders/FlatColor.glsl");
} 

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(const Emerald::Timestep& timestep)
{
	m_CameraController.OnUpdate(timestep);

	Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Emerald::RenderCommand::Clear();

	Emerald::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Emerald::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray);

	Emerald::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Emerald::Event& event)
{
	m_CameraController.OnEvent(event);
}