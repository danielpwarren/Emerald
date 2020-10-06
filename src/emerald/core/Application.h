#pragma once

#include "core/Base.h"
#include "core/Window.h"
#include "core/LayerStack.h"

#include "core/Timestep.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"

#include "imgui/ImGuiLayer.h"

namespace Emerald {

	class Application
	{
	public:
		Application(const std::string& title = "Emerald Application");
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
