#include "include/Emerald.h"
#include "core/EntryPoint.h"

#include "Sandbox2D.h"

class Sandbox : public Emerald::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{
	}
private:
};

Emerald::Application* Emerald::CreateApplication()
{
	return new Sandbox();
}
