#include "include/Emerald.h"
#include "core/EntryPoint.h"

#include "GameLayer.h"

class Sandbox : public Emerald::Application
{
public:
	Sandbox()
	{
		m_GameLayer = new GameLayer();
		PushLayer(m_GameLayer);
	}
	~Sandbox()
	{
		PopLayer(m_GameLayer);
	}
private:
	Emerald::Layer* m_GameLayer;
};

Emerald::Application* Emerald::CreateApplication()
{
	return new Sandbox();
}
