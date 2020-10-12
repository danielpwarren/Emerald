#pragma once

#include <include/Emerald.h>

#include "Random.h"

class Player
{
public:
	Player();

	void LoadAssests();

	void OnUpdate(Emerald::Timestep timestep);
	void OnRender();

	const glm::vec2& GetPosition() const { return m_Position; }
private:
	glm::vec2 m_Position = { 0.0f, 0.0f };

	float m_PlayerMoveSpeed = 10.0f;

	Emerald::Ref<Emerald::Texture2D> m_PlayerTexture;
};