#include "Propch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ProEngine/Math/Transform.h"

namespace Pro 
{
	OrthographicCamera::OrthographicCamera(float aspectRatio)
		: Camera(Math::ortho(-aspectRatio, aspectRatio, -1, 1), Mat4(1.0f))
	{
		PRO_PROFILE_FUNCTION();

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: Camera(Math::ortho(left, right, bottom, top), Mat4(1.0f))
	{
		PRO_PROFILE_FUNCTION();

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		PRO_PROFILE_FUNCTION();

		Mat4 transform = Math::translate(Mat4(1.0f), m_position);
		transform = Math::rotate(transform, glm::radians(m_rotation), Vec3(0, 0, 1));

		m_viewMatrix = Math::inverse(transform);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		PRO_PROFILE_FUNCTION();
		
		m_projectionMatrix = Math::ortho(left, right, bottom, top);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
}