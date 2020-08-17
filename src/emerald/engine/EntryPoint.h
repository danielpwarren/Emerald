#pragma once

extern Emerald::Application* Emerald::CreateApplication();

int main(int argc, char** argv)
{
	Emerald::Log::Init();
	EM_CORE_WARN("Initialized Log!");

	auto app = Emerald::CreateApplication();
	app->Run();
	delete app;
}