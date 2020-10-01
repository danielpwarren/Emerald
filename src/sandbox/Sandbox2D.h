#pragma once

#include "include/Emerald.h"

class Sandbox2D : public Emerald::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override; 
	virtual void OnDetach() override;

	void OnUpdate(const Emerald::Timestep& timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Emerald::Event& event) override;
private:
	Emerald::OrthographicCameraController m_CameraController;

	// Temp
	Emerald::Ref<Emerald::Shader> m_FlatColorShader;
	Emerald::Ref<Emerald::VertexArray> m_SquareVertexArray;

	glm::vec4 m_SquareColor = { 0.2f, 0.2f, 0.2f, 1.0f };
};