#include "EditorLayer.h"

#include "imgui/imgui.h"

namespace Emerald {

	EditorLayer::EditorLayer()
		: Layer("Editor Layer"), m_CameraController(1280.0f / 720.0f, true)
	{
		EM_PROFILE_FUNCTION();
	}

	void EditorLayer::OnAttach()
	{
		EM_PROFILE_FUNCTION();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnDetach()
	{
		EM_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(const Timestep& timestep)
	{
		EM_PROFILE_FUNCTION();

		if (m_ViewportFocused)
			m_CameraController.OnUpdate(timestep);

		m_Framebuffer->Bind();
		Renderer2D::ResetStats();
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y <= 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x <= 5.0f; x += 0.5f)
			{
				glm::vec4 color = { 0.5f, (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.7f };
				Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		EM_PROFILE_FUNCTION();

		static bool dockingEnabled = true;
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Emerald Editor", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Emerald::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		glm::vec2 viewportPanelSize = *((glm::vec2*)&ImGui::GetContentRegionAvail());
		if (m_ViewportSize != viewportPanelSize)
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		}
		m_ViewportSize = viewportPanelSize;
		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EM_PROFILE_FUNCTION();

		m_CameraController.OnEvent(event);
	}

}