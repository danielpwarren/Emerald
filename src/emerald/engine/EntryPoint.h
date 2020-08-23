#pragma once

extern Emerald::Application* Emerald::CreateApplication();

int main(int argc, char** argv)
{
	Emerald::Log::Init();

	auto app = Emerald::CreateApplication();
	app->Run();
	delete app;
}
