#pragma once

namespace Pro {
	struct Vec4 {
		float x, y, z, w;

		Vec4() : x(0), y(0), z(0), w(0) {}
		
		Vec4(float x, float y, float z, float w)
			:x(x), y(y), z(z), w(w)
		{}

		Vec4(const Vec4& v)
			:x(v.x), y(v.y), z(v.z), w(v.w)
		{}

		Vec4(const float& f)
			:x(f), y(f), z(f), w(f)
		{}

		float& operator[](const std::size_t& idx) {
			switch (idx)
			{
			case 0: return this->x;
			case 1: return this->y;
			case 2: return this->z;
			case 3: return this->w;
			}

		}

		const float& operator[](const std::size_t& idx) const {
			switch (idx)
			{
			case 0: return this->x;
			case 1: return this->y;
			case 2: return this->z;
			case 3: return this->w;
			}
			return -1;
		}

		Vec4 operator*(const float& f) const {
			return Vec4(this->x * f, this->y * f, this->z * f, this->w * f);
		}


		static Vec4 mul(Vec4 const& a, Vec4 const& b)
		{
			return Vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		}

		Vec4& operator*=(Vec4 const& v)
		{
			return (*this = mul(*this, Vec4(v)));
		}

		Vec4 operator*(const Vec4& v) const
		{
			return Vec4(v) *= *this;
		}

		Vec4 add(Vec4 const& a, Vec4 const& b)
		{
			return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		Vec4& operator+=(Vec4 const& v)
		{
			return (*this = add(*this, Vec4(v)));
		}

		Vec4 operator+(Vec4 const& v)
		{
			return Vec4(v) += *this;
		}

		const Vec4 operator+(Vec4 const& v) const
		{
			return Vec4(v) += *this;
		}

		Vec4 sub(const Vec4& a, const Vec4& b)
		{
			return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}

		Vec4& operator-=(const Vec4& v)
		{
			return (*this = sub(*this, v));
		}

		Vec4 operator-(const Vec4& v)
		{
			return Vec4(*this) -= v;
		}

		/*

		Vec4 operator=(const Vec4& v) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;

			return *this;
		}
		*/
	};
}
