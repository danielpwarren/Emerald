#include "include/Emerald.h"
#include "core/EntryPoint.h"

#include "GameLayer.h"

class EmeraldApp : public Emerald::Application
{
public:
	EmeraldApp()
	{
		m_GameLayer = new GameLayer();
		PushLayer(m_GameLayer);
	}
	~EmeraldApp()
	{
		PopLayer(m_GameLayer);
	}
private:
	Emerald::Layer* m_GameLayer;
};

Emerald::Application* Emerald::CreateApplication()
{
	return new EmeraldApp();
}
