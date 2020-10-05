#pragma once

extern Emerald::Application* Emerald::CreateApplication();

int main(int argc, char** argv)
{
	Emerald::Log::Init();

	EM_PROFILE_BEGIN_SESSION("Startup", "EmeraldProfile-Startup.json");
	auto app = Emerald::CreateApplication();
	EM_PROFILE_END_SESSION();

	EM_PROFILE_BEGIN_SESSION("Runtime", "EmeraldProfile-Runtime.json");
	app->Run();
	EM_PROFILE_END_SESSION();

	EM_PROFILE_BEGIN_SESSION("Shutdown", "EmeraldProfile-Shutdown.json");
	delete app;
	EM_PROFILE_END_SESSION();
}
