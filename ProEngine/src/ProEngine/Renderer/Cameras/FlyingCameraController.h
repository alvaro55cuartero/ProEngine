#pragma once
#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Events/ApplicationEvent.h"
#include <ProEngine/Renderer/Cameras/PerspectiveCamera.h>


namespace Pro
{
	class FlyingCameraController
	{
	public:
		FlyingCameraController(float fov, float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_camera; }
		const PerspectiveCamera& GetCamera() const { return m_camera; }

		void SetPosition(const Vec3& pos);
		void Rotate(const float& angle, const Vec3& axis);
		
	private:
		//bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		PerspectiveCamera m_camera;

		Vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		Vec3 direction = { 0.0f, 0.0f, 1.0f };
		float pitch = 0.0f;
		float yaw = 0.0f;

		float m_cameraTranslationSpeed = 5.0f;
		float m_cameraRotationSpeed = 180.0f;
	};
}