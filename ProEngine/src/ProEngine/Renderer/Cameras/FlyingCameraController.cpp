#include "Propch.h"
#include "FlyingCameraController.h"
#include "ProEngine/Core/Application.h"
#include "ProEngine/Core/KeyCodes.h"
#include <ProEngine/Math/Transform.h>
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtx/quaternion.hpp>


namespace Pro
{

	FlyingCameraController::FlyingCameraController(float fov, float aspectRatio)
		: m_aspectRatio(aspectRatio), m_camera(fov, m_aspectRatio)
	{}

	void FlyingCameraController::OnUpdate(Timestep delta)
	{
		PRO_PROFILE_FUNCTION();
		auto input = Pro::Application::Get().GetWindow().GetInput();

		float yawSign = m_camera.GetUpDirection().y < 0 ? -1.0f : 1.0f;
		yaw += yawSign * input->GetMouseDXImpl() * 0.3f * delta ;
		pitch += input->GetMouseDYImpl() * 0.3f * delta;
		auto rot = Quaternion(Vec3(pitch, yaw, 0.0f));
		m_camera.SetRotation(rot);
		auto m_cameraPosition = m_camera.GetPosition();

		if (input->IsMouseButtonPressedImpl(Key::W))
		{
			m_cameraPosition -= m_camera.GetForwardDirection() * delta;
		}

		if (input->IsMouseButtonPressedImpl(Key::S))
		{
			m_cameraPosition += m_camera.GetForwardDirection() * delta;
		}

		if (input->IsMouseButtonPressedImpl(Key::D))
		{
			m_cameraPosition += m_camera.GetRightDirection() * delta;
		}

		if (input->IsMouseButtonPressedImpl(Key::A))
		{
			m_cameraPosition -= m_camera.GetRightDirection() * delta;
		}

		if (input->IsMouseButtonPressedImpl(Key::Space)) 
		{
			m_cameraPosition.y +=  delta;
		}

		if (input->IsMouseButtonPressedImpl(Key::LeftShift))
		{
			m_cameraPosition.y -= delta;
		}
		
		m_camera.SetPosition(m_cameraPosition);

	}

	void FlyingCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		//dispatcher.Dispatch<WindowResizeEvent>(PRO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
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
	bool FlyingCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		PRO_PROFILE_FUNCTION();
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}


	void FlyingCameraController::SetPosition(const Vec3& pos)
	{
		m_camera.SetPosition(pos);
	}
	void FlyingCameraController::Rotate(const float& angle, const Vec3& axis)
	{
		m_camera.Rotate(angle, axis);
	}
}

