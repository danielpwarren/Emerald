#include "Level.h"

void Level::Init()
{
	for (int column = 0; column < m_TileMap.size(); column++) {
		for (int row = 0; row < m_TileMap[column].size(); row++) {
			int x = column - m_TileMap.size() / 2;
			int y = row - m_TileMap[column].size() / 2;
			Tile& tile = m_TileMap[column][row];
			tile.Position = glm::vec3(x, y, -0.9f);
			tile.Color = glm::vec4((float)column/m_TileMap.size(), (float)row/m_TileMap[column].size(), (float)column+(float)row/m_TileMap.size()+m_TileMap[column].size(), 1.0f);
		}
	}
	
	m_Player.LoadAssests();
}

void Level::OnUpdate(Emerald::Timestep timestamp)
{
	m_Player.OnUpdate(timestamp);
}

void Level::OnRender()
{
	DrawMap();

	m_Player.OnRender();
}

void Level::SetTileMapSize(int width, int height)
{
	m_TileMap.resize(height);
	for (auto& vec : m_TileMap)
		vec.resize(width);
}

void Level::DrawMap()
{
	for (int column = 0; column < m_TileMap.size(); column++) {
		for (int row = 0; row < m_TileMap[column].size(); row++) {
			Tile& tile = m_TileMap[column][row];
			Emerald::Renderer2D::DrawQuad({ tile.Position }, { 1.0f, 1.0f }, tile.Color);
		}
	}
}