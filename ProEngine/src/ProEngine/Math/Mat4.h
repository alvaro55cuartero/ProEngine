#pragma once
#include "Vec4.h"

namespace Pro 
{
	struct Mat4 
	{
		Mat4()
			: data{ Vec4(), Vec4(), Vec4(), Vec4() }
		{}

		Mat4(
			const float& x0, const float& y0, const float& z0, const float& w0,
			const float& x1, const float& y1, const float& z1, const float& w1,
			const float& x2, const float& y2, const float& z2, const float& w2,
			const float& x3, const float& y3, const float& z3, const float& w3
		)
			: data{
				Vec4(x0, y0, z0, w0),
				Vec4(x1, y1, z1, w1),
				Vec4(x2, y2, z2, w2),
				Vec4(x3, y3, z3, w3)
		}
		{}

		Mat4(const float& f)
			: data{ Vec4(f, 0, 0, 0), Vec4(0, f, 0, 0), Vec4(0, 0, f, 0), Vec4(0, 0, 0, f) }
		{}


		Mat4(const Vec4& v0, const Vec4& v1, const Vec4& v2, const Vec4& v3)
			: data{ Vec4(v0), Vec4(v1), Vec4(v2), Vec4(v3) }
		{}




		Vec4& operator[](const std::size_t& idx) {
			return this->data[idx];
		}
		const Vec4& operator[](const std::size_t& idx) const {
			return this->data[idx];
		}



		Mat4 operator*(const float& s)
		{

			return Mat4(
				this->data[0] * s,
				this->data[1] * s,
				this->data[2] * s,
				this->data[3] * s);
		}


		Vec4 operator*(Vec4 const& v ) const
		{
			Vec4 const Mov0(v[0]);
			Vec4 const Mov1(v[1]);
			Vec4 const Mul0 = this->data[0] * Mov0;
			Vec4 const Mul1 = this->data[1] * Mov1;
			Vec4 const Add0 = Mul0 + Mul1;
			Vec4 const Mov2(v[2]);
			Vec4 const Mov3(v[3]);
			Vec4 const Mul2 = this->data[2] * Mov2;
			Vec4 const Mul3 = this->data[3] * Mov3;
			Vec4 const Add1 = Mul2 + Mul3;
			Vec4 const Add2 = Add0 + Add1;

			return Add2;
		}

		Vec4 operator*(Vec4 const& v)
		{
			Vec4 const Mov0(v[0]);
			Vec4 const Mov1(v[1]);
			Vec4 const Mul0 = this->data[0] * Mov0;
			Vec4 const Mul1 = this->data[1] * Mov1;
			Vec4 const Add0 = Mul0 + Mul1;
			Vec4 const Mov2(v[2]);
			Vec4 const Mov3(v[3]);
			Vec4 const Mul2 = this->data[2] * Mov2;
			Vec4 const Mul3 = this->data[3] * Mov3;
			Vec4 const Add1 = Mul2 + Mul3;
			Vec4 const Add2 = Add0 + Add1;

			return Add2;
		}

		inline const Mat4 operator* (Mat4 const& m) const {
			Mat4 const m1 = *this;
			Mat4 const m2 = m;

			Vec4 const SrcA0 = m1[0];
			Vec4 const SrcA1 = m1[1];
			Vec4 const SrcA2 = m1[2];
			Vec4 const SrcA3 = m1[3];

			Vec4 const SrcB0 = m2[0];
			Vec4 const SrcB1 = m2[1];
			Vec4 const SrcB2 = m2[2];
			Vec4 const SrcB3 = m2[3];
			Mat4 result;

			result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
			result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
			result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
			result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];

			return result;
		}

		inline Mat4 operator* (Mat4 const& m)
		{
			Mat4 const m1 = *this;
			Mat4 const m2 = m;

			Vec4 const SrcA0 = m1[0];
			Vec4 const SrcA1 = m1[1];
			Vec4 const SrcA2 = m1[2];
			Vec4 const SrcA3 = m1[3];
			
			Vec4 const SrcB0 = m2[0];
			Vec4 const SrcB1 = m2[1];
			Vec4 const SrcB2 = m2[2];
			Vec4 const SrcB3 = m2[3];
			Mat4 result;

			result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
			result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
			result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
			result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
			
			return result;
		}

		Mat4(const Mat4& src) 
			: data{ Vec4(src[0]), Vec4(src[1]), Vec4(src[2]), Vec4(src[3]) }
		{}

		std::string ToString() const
		{
			std::stringstream r;
			r << data[0][0] << ", " << data[0][1] << ", " << data[0][2] << ", " << data[0][3] << "\n";
			r << data[1][0] << ", " << data[1][1] << ", " << data[1][2] << ", " << data[1][3] << "\n";
			r << data[2][0] << ", " << data[2][1] << ", " << data[2][2] << ", " << data[2][3] << "\n";
			r << data[3][0] << ", " << data[3][1] << ", " << data[3][2] << ", " << data[3][3] << "\n";

			return r.str();
		}

		std::string ToString()
		{
			std::stringstream r;
			r << data[0][0] << ", " << data[0][1] << ", " << data[0][2] << ", " << data[0][3] << "\n";
			r << data[1][0] << ", " << data[1][1] << ", " << data[1][2] << ", " << data[1][3] << "\n";
			r << data[2][0] << ", " << data[2][1] << ", " << data[2][2] << ", " << data[2][3] << "\n";
			r << data[3][0] << ", " << data[3][1] << ", " << data[3][2] << ", " << data[3][3] << "\n";

			return r.str();
		}
		



	private:
		Vec4 data[4];
	};

}
