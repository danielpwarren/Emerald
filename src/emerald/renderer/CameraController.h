#pragma once

#include "renderer/Camera.h"

#include "core/Timestep.h"

#include "events/ApplicationEvent.h"
#include "events/MouseEvent.h"

namespace Emerald {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool variableZoom = false, bool rotation = false);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }
	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		bool m_Rotation;
		bool m_VariableZoom;
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 0.0f, m_CameraRotationSpeed = 90.0f;
	};

}