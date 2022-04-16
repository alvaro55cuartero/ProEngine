#pragma once

#include "ProEngine/Events/ApplicationEvent.h"
#include "ProEngine/Core/LayerStack.h"
#include "ProEngine/Core/Window.h"
#include "ProEngine/Core/Layer.h"

int main();

namespace Pro 
{
	class Application
	{

	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		inline Window& GetWindow() { return *m_window; }

		void Close();

		inline static Application& Get() { return *s_Instance; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_LayerStack;
		Window* m_window;

	private:
		static Application* s_Instance;
		friend int ::main();
	};

	Application* CreateApplication();
}