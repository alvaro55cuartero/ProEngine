#include "Propch.h"
#include "Quaternion.h"


namespace Pro
{

	Quaternion::Quaternion()
		:w(1.0f), x(0), y(0), z(0)
	{}

	Quaternion::Quaternion(float angle, Vec3 axis)
	{
		float const a(angle);
		float const s = (float)::sin(a * 0.5);
		w = ::cos(a * 0.5);
		auto b = axis * s;
		x = b.x;
		y = b.y;
		z = b.z;
	}

	Quaternion::Quaternion(Vec3 const& eulerAngle)
	{
		Vec3 c = cos(eulerAngle * 0.5);
		Vec3 s = sin(eulerAngle * 0.5);

		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

	void Rotate(float angle, Vec3 axis)
	{

	}

	float Quaternion::GetAngle()
	{
		return 0;
	}

	EulerAngle Quaternion::ToEulerAngle()
	{
		return EulerAngle();
	}

	Mat4 Quaternion::ToMat4()
	{
		Mat4 result(1.0f);

		float qxx(x * x);
		float qyy(y * y);
		float qzz(z * z);
		float qxz(x * z);
		float qxy(x * y);
		float qyz(y * z);
		float qwx(w * x);
		float qwy(w * y);
		float qwz(w * z);

		result[0][0] = 1 - 2 * (qyy + qzz);
		result[0][1] = 2 * (qxy + qwz);
		result[0][2] = 2 * (qxz - qwy);

		result[1][0] = 2 * (qxy - qwz);
		result[1][1] = 1 - 2 * (qxx + qzz);
		result[1][2] = 2 * (qyz + qwx);

		result[2][0] = 2 * (qxz + qwy);
		result[2][1] = 2 * (qyz - qwx);
		result[2][2] = 1 - 2 * (qxx + qyy);

		return result;
	}

	Quaternion Quaternion::mul(Quaternion const& q) const
	{
		Quaternion res;
		float a = (q.w * w) - GetVec3() * q.GetVec3();
		Vec3 b = GetVec3() * q.w + q.GetVec3() * w + (GetVec3().Cross(q.GetVec3()));
		res.x = b.x;
		res.y = b.y;
		res.z = b.z;
		res.w = a;

		return res;
	}

	Quaternion Quaternion::operator*(Quaternion const& q) const
	{
		return this->mul(q);
	}

	void Quaternion::Rotate(float angle, Vec3 axis)
	{
		Quaternion a(angle, axis);
		//std::cout << a.w << " " << a.x << " " << a.y << " " << a.z << "" << std::endl;
		auto b = this->mul(a);
		w = b.w;
		x = b.x;
		y = b.y;
		z = b.z;

	}

	Vec3 Quaternion::operator*(Vec3 const& v) const
	{
		Vec3 const uv(GetVec3().Cross(v));
		Vec3 const uuv(GetVec3().Cross(uv));

		return v + ((uv * w) + uuv) * 2;
	}




}