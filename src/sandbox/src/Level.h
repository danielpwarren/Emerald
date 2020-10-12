#pragma once

#include "Player.h"

struct Tile
{
	glm::vec3 Position;
	glm::vec4 Color;
};

class Level
{
public:
	void Init();

	void OnUpdate(Emerald::Timestep timestamp);
	void OnRender();

	Player& GetPlayer() { return m_Player; }

	void SetTileMapSize(int width, int height);
private:
	void DrawMap();
private:
	std::vector<std::vector<Tile>> m_TileMap;
	Player m_Player;
};