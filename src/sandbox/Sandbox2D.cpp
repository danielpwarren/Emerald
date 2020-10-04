#include "Sandbox2D.h"

#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_EmeraldLogo = Emerald::Texture2D::Create("assets/textures/Emerald.png");
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
	for (int y = -5; y <= 5; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			Emerald::Renderer2D::DrawQuad({ x * 0.11f, y * 0.11f, -0.1f }, { 0.1f, 0.1f }, m_SquareColor);
		}
	}

	Emerald::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureRotation, m_EmeraldLogo);

	Emerald::Renderer2D::EndScene();

	m_TextureRotation += 1.0f;
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