#pragma once
#include <ProEngine/Math/Mat4.h>
#include <ProEngine/Math/Vec3.h>

namespace Pro 
{
	class EulerAngle
	{
		
	};


	class Quaternion 
	{
	public:
		Quaternion();
		Quaternion(float angle, Vec3 axis);
		Quaternion(Vec3 const& eulerAngle);


		void Rotate(float angle, Vec3 axis);

		float GetAngle();
		EulerAngle ToEulerAngle();
		Mat4 ToMat4();
		
		Vec3 GetVec3() const { return Vec3(x, y, z); };

		Quaternion mul(Quaternion const& q) const;
		Quaternion operator*(Quaternion const& q) const;
		Vec3 operator*(Vec3 const& q) const;



	public:
		float x, y, z, w;

	};


}