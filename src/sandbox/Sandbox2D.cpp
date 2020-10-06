#include "Sandbox2D.h"

#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	EM_PROFILE_FUNCTION();

	Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
} 

void Sandbox2D::OnDetach()
{
	EM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(const Emerald::Timestep& timestep)
{
	EM_PROFILE_FUNCTION();

	m_Framerate = 1 / timestep;

	m_CameraController.OnUpdate(timestep);

	Emerald::RenderCommand::Clear();

	Emerald::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Emerald::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
	Emerald::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	EM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::Text("Framerate: %d", m_Framerate);
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Emerald::Event& event)
{
	m_CameraController.OnEvent(event);
}