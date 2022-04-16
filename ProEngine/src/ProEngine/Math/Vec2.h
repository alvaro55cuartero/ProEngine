#pragma once
#include <cstddef>
#include <iostream>

namespace Pro
{

	struct Vec2 {
		float x, y;

		Vec2() : x(0), y(0) {}

		Vec2(float f)
			:x(f), y(f)
		{}

		Vec2(float x, float y)
			:x(x), y(y)
		{}

		const float& operator[](const std::size_t& idx) const {
			switch (idx)
			{
			case 0: return this->x;
			case 1: return this->y;
			}
			return 0;
		}

		static Vec2 mul(Vec2 const& a, Vec2 const& b)
		{
			return Vec2(a.x * b.x, a.y * b.y);
		}

		Vec2& operator*=(Vec2 const& v)
		{
			return (*this = mul(*this, Vec2(v)));
		}


		Vec2 operator*(float const& f) const
		{
			return Vec2(this->x * f, this->y * f);
		}

		Vec2 operator*(Vec2 const& v) const
		{
			return Vec2(this->x * v.x, this->y * v.y);
		}

		Vec2 operator+(const Vec2& v) const
		{
			return Vec2(this->x + v.x, this->y + v.y);
		}

		Vec2 operator+=(const Vec2& v)
		{
			return  (*this = v + *this);
		}

		Vec2 operator-(const Vec2& v) const
		{
			return Vec2(this->x - v.x, this->y - v.y);
		}


		Vec2 operator/(Vec2 const& f) const
		{
			return Vec2(this->x / f.x, this->y / f.y);
		}

	};
}