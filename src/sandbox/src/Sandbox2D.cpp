#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	EM_PROFILE_FUNCTION();

	Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	m_EmeraldLogo = Emerald::Texture2D::Create("assets/textures/Emerald.png");
}

void Sandbox2D::OnDetach()
{
	EM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(const Emerald::Timestep& timestep)
{
	EM_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(timestep);

	Emerald::Renderer2D::ResetStats();

	Emerald::RenderCommand::Clear();

	Emerald::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y <= 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x <= 5.0f; x += 0.5f)
		{
			glm::vec4 color = { 0.5f, (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.7f };
			Emerald::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	m_LogoRotation += 15.0f * timestep;
	Emerald::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, glm::radians(m_LogoRotation), m_EmeraldLogo);
	Emerald::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	EM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Emerald::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void Sandbox2D::OnEvent(Emerald::Event& event)
{
	EM_PROFILE_FUNCTION();

	m_CameraController.OnEvent(event);
}

