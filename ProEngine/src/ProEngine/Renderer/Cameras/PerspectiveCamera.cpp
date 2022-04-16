#include "Propch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ProEngine/Math/Transform.h"
#include <glm/ext/quaternion_float.hpp>

namespace Pro
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
		: Camera(Math::perspective(Math::radians(fov), aspectRatio, 1.0f, 100.0f), Mat4(1.0f))
	{
		PRO_PROFILE_FUNCTION();

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}


	void PerspectiveCamera::RecalculateViewMatrix()
	{
		PRO_PROFILE_FUNCTION();

		Mat4 transform = Math::translate(Mat4(1.0f), m_position) * m_rotation.ToMat4();
		m_viewMatrix = Math::inverse(transform);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float bottom, float top)
	{
		PRO_PROFILE_FUNCTION();
		m_projectionMatrix = Math::perspective(Math::radians(fov),aspectRatio, 1, 1000);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCamera::Rotate(float angle, Vec3 axis)
	{
		m_rotation.Rotate(angle, axis);
		RecalculateViewMatrix();
	}

	Vec3 PerspectiveCamera::GetUpDirection()
	{
		return m_rotation * Vec3(0, 1, 0);
	}

	Vec3 PerspectiveCamera::GetRightDirection()
	{
		return m_rotation * Vec3(1, 0, 0);
	}

	Vec3 PerspectiveCamera::GetForwardDirection()
	{
		return m_rotation * Vec3(0, 0, 1);

	}

}