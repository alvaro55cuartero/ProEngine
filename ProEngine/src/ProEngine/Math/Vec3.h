#pragma once
#include "Vec4.h"
#include "Vec2.h"

namespace Pro 
{

	struct Vec3 {
		float x, y, z;

		Vec3() : x(0), y(0), z(0) {}

		Vec3(float f)
			:x(f), y(f), z(f)
		{}

		Vec3(float x, float y, float z)
			:x(x), y(y), z(z)
		{}
		
		Vec3(const Vec2& v)
			: x(v.x), y(v.y), z(0)
		{}

		Vec3(const Vec4& v)
			: x(v.x), y(v.y), z(v.z)
		{}

		operator Vec2() const { return Pro::Vec2(x, y); }

		const float& operator[](const std::size_t& idx) const {
			switch (idx)
			{
			case 0: return this->x;
			case 1: return this->y;
			case 2: return this->z;
			}
			return 0;
		}

		static Vec3 mul(Vec3 const& a, Vec3 const& b)
		{
			return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
		}

		Vec3& operator*=(Vec3 const& v)
		{
			return (*this = mul(*this, Vec3(v)));
		}

		Vec3 operator/(float& f)
		{
			return Vec3(this->x / f, this->y / f, this->z / f);
		}

		Vec3 operator/(float const& f) const
		{
			return Vec3(this->x / f, this->y / f, this->z / f);
		}

		Vec3& operator/=(float& f)
		{
			return (*this = *this / f);
		}


		Vec3 operator*(float const& f) const
		{
			return Vec3(this->x * f, this->y * f, this->z * f);
		}

		Vec3 operator*(float& f)
		{
			return Vec3(this->x * f, this->y * f, this->z * f);
		}

		float operator*(Vec3 const& v) const
		{
			return (this->x *v.x) + (this->y * v.y) + (this->z * v.z);
		}

		Vec3 operator+(const Vec3& v) const
		{
			return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
		}

		Vec3& operator+=(Vec3 const& v)
		{
			return (*this = *this + Vec3(v));
		}

		Vec3& operator-=(Vec3 const& v)
		{
			return (*this = *this - Vec3(v));
		}

		Vec3 operator-(const Vec3& v) const
		{
			return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
		}

		Vec3 Cross(const Vec3& v) const
		{
			return Vec3(
			y * v.z - v.y * z,
			z * v.x - v.z * x,
			x * v.y - v.x * y);
		}
	};


	static Vec3 cos(Vec3 in) {
		return Vec3(::cos(in.x), ::cos(in.y), ::cos(in.z));
	}

	static Vec3 sin(Vec3 in) {
		return Vec3(::sin(in.x), ::sin(in.y), ::sin(in.z));
	}
}