#pragma once

#include "include/Emerald.h"

namespace Emerald {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(const Timestep & timestep) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event & event) override;
	private:
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0, 0 };
	};
}