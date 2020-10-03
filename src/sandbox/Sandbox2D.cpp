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
	
} 

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(const Emerald::Timestep& timestep)
{
	m_CameraController.OnUpdate(timestep);

	Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Emerald::RenderCommand::Clear();

	Emerald::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Emerald::Renderer2D::DrawQuad({ 0.0f, 0.0f, }, { 1.0f, 1.0f }, m_SquareColor);

	Emerald::Renderer2D::EndScene();
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