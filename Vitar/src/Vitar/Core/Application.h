#pragma once

#include "Base.h"
#include "../Events/Event.h"
#include "Window.h"
#include "../Events/ApplicationEvent.h"
#include "Vitar/Core/LayerStack.h"

#include "Vitar/Core/Timestep.h"

#include "Vitar/ImGui/ImGuiLayer.h"

namespace Vitar 
{
	class VITAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;

		LayerStack m_LayerStack;

		Timestep m_TimeStep;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

