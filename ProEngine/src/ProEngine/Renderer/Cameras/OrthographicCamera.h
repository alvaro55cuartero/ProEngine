#pragma once
#include "ProEngine/Math/Math.h"
#include "Camera.h"

class Camera
{
};

namespace Pro 
{
	class OrthographicCamera: public Camera
	{
	public:
		OrthographicCamera(float aspectRatio);
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const Vec3& GetPosition() const { return m_position; }
		void SetPosition(const Vec3& position) { m_position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_rotation; }
		void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
		
	private:
		void RecalculateViewMatrix();


	public:

		Vec3 m_position;
		float m_rotation = 0.0f;
	};
}