#include "core/empch.h"
#include "renderer/CameraController.h"

#include "input/Input.h"
#include "input/KeyCodes.h"

namespace Emerald {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool variableZoom, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_VariableZoom(variableZoom), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		EM_PROFILE_FUNCTION();

		m_CameraTranslationSpeed = m_ZoomLevel * 1.25f;

		if (Input::IsKeyPressed(EM_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(EM_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(EM_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(EM_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(EM_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * timestep;

			if (Input::IsKeyPressed(EM_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * timestep;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		if (m_VariableZoom)
			dispatcher.Dispatch<MouseScrolledEvent>(EM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		EM_PROFILE_FUNCTION();

		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 10.0f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		EM_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		CalculateView();
		return false;
	}

}