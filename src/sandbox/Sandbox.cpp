#include "include/Emerald.h"
#include "core/EntryPoint.h"

#include "Sandbox2D.h"

class Sandbox : public Emerald::Application
{
public:
	Sandbox()
	{
		m_Sandbox2D = new Sandbox2D();
		PushLayer(m_Sandbox2D);
	}
	~Sandbox()
	{
		PopLayer(m_Sandbox2D);
	}
private:
	Emerald::Layer* m_Sandbox2D;
};

Emerald::Application* Emerald::CreateApplication()
{
	return new Sandbox();
}
