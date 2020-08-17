#include <include/Emerald.h>

class ExampleLayer : public Emerald::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
    }

    void OnEvent(Emerald::Event& event) override
    {
    }
};

class Sandbox : public Emerald::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {
    }
};

Emerald::Application* Emerald::CreateApplication()
{
    return new Sandbox();
}
