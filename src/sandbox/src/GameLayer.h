#pragma once

#include "include/Emerald.h"

#include "glm/glm.hpp"
#include "Level.h"

class GameLayer : public Emerald::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(const Emerald::Timestep& timestep) override;
	void OnEvent(Emerald::Event& event);
	bool OnWindowResize(Emerald::WindowResizeEvent& event);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Emerald::Scope<Emerald::OrthographicCamera> m_Camera;
	Level m_Level;
	float m_Time = 0.0f;
	
	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};