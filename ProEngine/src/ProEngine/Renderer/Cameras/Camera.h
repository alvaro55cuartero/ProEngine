#pragma once
#include "ProEngine/Math/Mat4.h"
#include "ProEngine/Math/Math.h"
#include "ProEngine/Math/Transform.h"

namespace Pro
{
	class Camera
	{
	public:
		Camera() = default;

		Camera(Mat4 projectionMatrix, Mat4 viewMatrix)
			:m_projectionMatrix(projectionMatrix), m_viewMatrix(viewMatrix)
		{}

		const Mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		const Mat4& GetViewMatrix() const { return m_viewMatrix; }
		const Mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

		void RecalculateViewMatrix()
		{
			Mat4 transform = Math::translate(Mat4(1.0f), m_position);
			m_viewMatrix = Math::inverse(transform);
			m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
		}

		const Vec3& GetPosition() const { return m_position; }
		void SetPosition(const Vec3& position) { m_position = position; RecalculateViewMatrix(); }


	public:
		Mat4 m_projectionMatrix;
		Mat4 m_viewMatrix;
		Mat4 m_viewProjectionMatrix;
		Vec3 m_position;
	};
}
