#pragma once

#include "core/Base.h"
#include "core/Window.h"
#include "core/LayerStack.h"

#include "core/Timestep.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"

#include "imgui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Emerald {

	class Application
	{
	public:
		Application(const std::string& title = "Emerald Application");
		virtual ~Application();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
