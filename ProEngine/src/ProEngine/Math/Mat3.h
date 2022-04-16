#pragma once
#include "Vec3.h"
#include <cstddef>

namespace Pro
{
	struct Mat3 
	{
		Mat3()
			: data{ Vec3(), Vec3(), Vec3() }
		{}

		Mat3(
			const float& x0, const float& y0, const float& z0,
			const float& x1, const float& y1, const float& z1,
			const float& x2, const float& y2, const float& z2
		)
			: data{
				Vec3(x0, y0, z0),
				Vec3(x1, y1, z1),
				Vec3(x2, y2, z2),
		}
		{}

		Mat3(const float& f)
			: data{ Vec3(f, 0, 0), Vec3(0, f, 0), Vec3(0, 0, f) }
		{}


		Mat3(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3)
			: data{ Vec3(v0), Vec3(v1), Vec3(v2) }
		{}




		Vec3& operator[](const std::size_t& idx) {
			return this->data[idx];
		}

		const Vec3& operator[](const std::size_t& idx) const {
			return this->data[idx];
		}


		Vec3& operator[](int i)
		{
			return this->data[i];
		}

		Vec3 const& operator[](int i) const
		{
			return this->data[i];
		}

		inline Mat3 operator* (Mat3 const& m)
		{
			Mat3 const m1 = m;
			Mat3 const m2 = *this;

			Vec3 const SrcA0 = m1[0];
			Vec3 const SrcA1 = m1[1];
			Vec3 const SrcA2 = m1[2];

			Vec3 const SrcB0 = m2[0];
			Vec3 const SrcB1 = m2[1];
			Vec3 const SrcB2 = m2[2];
			Mat3 result;

			result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2];
			result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2];
			result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2];

			return result;
		}

		Mat3(const Mat3& src)
			: data{ Vec3(src[0]), Vec3(src[1]), Vec3(src[2]) }
		{}


	private:
		Vec3 data[3];
	};
}