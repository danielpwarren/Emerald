#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player()
{

}

void Player::LoadAssests()
{
	m_PlayerTexture = Emerald::Texture2D::Create("assets/textures/Player.png");
}

void Player::OnUpdate(Emerald::Timestep timestep)
{
	if (Emerald::Input::IsKeyPressed(EM_KEY_W))
	{
		m_Position.y += m_PlayerMoveSpeed * timestep;
	}

	if (Emerald::Input::IsKeyPressed(EM_KEY_A))
	{
		m_Position.x -= m_PlayerMoveSpeed * timestep;
	}

	if (Emerald::Input::IsKeyPressed(EM_KEY_S))
	{
		m_Position.y -= m_PlayerMoveSpeed * timestep;
	}

	if (Emerald::Input::IsKeyPressed(EM_KEY_D))
	{
		m_Position.x += m_PlayerMoveSpeed * timestep;
	}
}

void Player::OnRender()
{
	Emerald::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, { 1.0f, 1.0f }, m_PlayerTexture);
}