#pragma once
#include "ProEngine/Math/Math.h"
#include "Camera.h"
#include <ProEngine/Math/Quaternion.h>

namespace Pro
{
	class PerspectiveCamera: public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio);

		void SetProjection(float left, float right, float bottom, float top);

		void RecalculateViewMatrix();


		//void SetProjection(float left, float right, float bottom, float top);

		const Vec3& GetPosition() const { return m_position; }
		void SetPosition(const Vec3& position) { m_position = position; RecalculateViewMatrix(); }

		//float GetRotation() const { return m_rotation; }
		//1void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

		void Rotate(float angle, Vec3 axis);
		void SetRotation(Quaternion quaternion) { m_rotation = quaternion; };
		Vec3 GetUpDirection();
		Vec3 GetRightDirection();
		Vec3 GetForwardDirection();


	public:

		Vec3 m_position;
		Quaternion m_rotation;

	};
}
