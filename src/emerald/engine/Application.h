#pragma once

#include "core/Base.h"
#include "engine/Window.h"
#include "engine/LayerStack.h"

#include "events/Event.h"
#include "events/ApplicationEvent.h"

#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"

#include "imgui/ImGuiLayer.h"

namespace Emerald {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_GreyShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
