#pragma once

#include "include/Emerald.h"

class Sandbox2D : public Emerald::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(const Emerald::Timestep& timestep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Emerald::Event& event) override;
private:
	Emerald::OrthographicCameraController m_CameraController;
};