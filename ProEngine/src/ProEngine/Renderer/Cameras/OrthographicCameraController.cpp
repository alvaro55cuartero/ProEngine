#include "Propch.h"
#include "ProEngine/Renderer/Cameras/OrthographicCameraController.h"
#include "ProEngine/Core/Application.h"
#include "ProEngine/Core/KeyCodes.h"
#include <ProEngine/Math/Transform.h>


namespace Pro 
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio* m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		PRO_PROFILE_FUNCTION();
		auto input = Pro::Application::Get().GetWindow().GetInput();

		if (input->IsMouseButtonPressedImpl(Key::A))
		{
			m_cameraPosition.x -= ::cos(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= ::sin(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		if (input->IsMouseButtonPressedImpl(Key::D))
		{
			m_cameraPosition.x += ::cos(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += ::sin(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		if (input->IsMouseButtonPressedImpl(Key::W))
		{
			m_cameraPosition.x += -::sin(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += ::cos(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		if (input->IsMouseButtonPressedImpl(Key::S))
		{
			m_cameraPosition.x -= -::sin(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= ::cos(Math::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		if (m_rotation)
		{
			if (input->IsMouseButtonPressedImpl(Key::Q))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			if (input->IsMouseButtonPressedImpl(Key::E))
				m_cameraRotation -= m_cameraRotationSpeed * ts;

			if (m_cameraRotation > 180.0f)
				m_cameraRotation -= 360.0f;
			else if (m_cameraRotation <= -180.0f)
				m_cameraRotation += 360.0f;

			m_camera.SetRotation(m_cameraRotation);
		}

		m_camera.SetPosition(m_cameraPosition);

		m_cameraTranslationSpeed = m_zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PRO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	/*
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	*/
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		PRO_PROFILE_FUNCTION();
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}
}
