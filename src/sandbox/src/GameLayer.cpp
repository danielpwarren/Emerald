#include "GameLayer.h"

#include "Random.h"

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Emerald::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	Emerald::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(const Emerald::Timestep& timestep)
{
	m_Time += timestep;

	m_Level.OnUpdate(timestep);

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	Emerald::RenderCommand::Clear();

	Emerald::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Emerald::Renderer2D::EndScene();
}

void GameLayer::OnEvent(Emerald::Event& event)
{
	Emerald::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Emerald::WindowResizeEvent>(EM_BIND_EVENT_FN(GameLayer::OnWindowResize));
}

bool GameLayer::OnWindowResize(Emerald::WindowResizeEvent& event)
{
	CreateCamera(event.GetWidth(), event.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Emerald::CreateScope<Emerald::OrthographicCamera>(left, right, bottom, top);

	m_Level.SetTileMapSize((top * 2) + 1, (right * 2) + 1);
	m_Level.Init();
}