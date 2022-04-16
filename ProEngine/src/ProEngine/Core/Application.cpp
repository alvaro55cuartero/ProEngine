#include "Propch.h"

#include "ProEngine/Core/Application.h"
#include "ProEngine/Core/Timestep.h"

#include "ProEngine/Renderer/Renderer.h"

#include "ProEngine/Debug/Instrumentor.h"


namespace Pro 
{

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		PRO_PROFILE_FUNCTION();
		s_Instance = this;

		m_window = Window::Create();
		m_window->SetEventCallback(PRO_BIND_EVENT_FN(Application::OnEvent));

		//Renderer::Init();
	}

	Application::~Application()
	{
		PRO_PROFILE_FUNCTION();
		//Renderer::Shutdown();
	}

	void Application::Close()
	{
		m_running = false;
	}

	void Application::PushLayer(Layer* layer) 
	{
		PRO_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
	}

	void Application::Run()
	{
		PRO_PROFILE_FUNCTION();
		auto timer = this->GetWindow().GetTimer();
		timer->Start();

		while (m_running) {
			PRO_PROFILE_SCOPE("RunLoop");

			Timestep delta = timer->GetDeltaTime();

			if (!m_minimized)
			{
				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
				RenderCommand::Clear();


				PRO_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(delta);
			}
			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		PRO_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(PRO_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(PRO_BIND_EVENT_FN(Application::OnWindowResize));



		for (Layer* layer : m_LayerStack) {
			layer->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
