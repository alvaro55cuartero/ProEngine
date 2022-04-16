#pragma once

#include "Mat4.h"
#include "Vec3.h"
#include <cmath>

namespace Pro 
{
	namespace Math
	{

		static float radians(float degrees)
		{
			return degrees * static_cast<float>(0.01745329251994329576923690768489);
		}

		static float inversesqrt(float x)
		{
			return (1) / sqrt(x);
		}

		static float dot(const Vec3& a, const Vec3& b)
		{
			Vec3 tmp(a * b);
			return tmp.x + tmp.y + tmp.z;
		}

		static Vec3 normalize(Vec3 const& v)
		{
			return v * inversesqrt(dot(v, v));
		}


		static Mat4 translate(const Mat4& m, const Vec3& v)
		{
			Mat4 result(m);
			result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
			return result;
		}


		static Mat4 rotate(const Mat4& m, float angle, const Vec3& v)
		{
			float const a = angle;
			float const c = ::cos(a);
			float const s = ::sin(a);

			Vec3 axis(normalize(v));
			Vec3 temp(axis * (1 - c));

			Mat4 Rotate;
			Rotate[0][0] = c + temp[0] * axis[0];
			Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
			Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

			Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
			Rotate[1][1] = c + temp[1] * axis[1];
			Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

			Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
			Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
			Rotate[2][2] = c + temp[2] * axis[2];

			Mat4 Result;
			Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
			Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
			Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
			Result[3] = m[3];
			return Result;
		}

		static Mat4 scale(const Mat4& m, const Vec3& v)
		{
			Mat4 result;
			result[0] = m[0] * v[0];
			result[1] = m[1] * v[1];
			result[2] = m[2] * v[2];
			result[3] = m[3];
			return result;
		}

		static Mat4 inverse(const Mat4& m)
		{
			float Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			float Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			float Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			float Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			float Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			float Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			float Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			float Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			float Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			float Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			float Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			float Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			float Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			float Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			float Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			float Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			float Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			float Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			Vec4 Fac0(Coef00, Coef00, Coef02, Coef03);
			Vec4 Fac1(Coef04, Coef04, Coef06, Coef07);
			Vec4 Fac2(Coef08, Coef08, Coef10, Coef11);
			Vec4 Fac3(Coef12, Coef12, Coef14, Coef15);
			Vec4 Fac4(Coef16, Coef16, Coef18, Coef19);
			Vec4 Fac5(Coef20, Coef20, Coef22, Coef23);

			Vec4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			Vec4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			Vec4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			Vec4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			Vec4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			Vec4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			Vec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			Vec4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			Vec4 SignA(+1, -1, +1, -1);
			Vec4 SignB(-1, +1, -1, +1);
			Mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			Vec4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			Vec4 Dot0(m[0] * Row0);
			float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			float OneOverDeterminant = 1 / Dot1;

			return Inverse * OneOverDeterminant;
		}

		static Mat4 ortho(float left, float right, float bottom, float top)
		{
			Mat4 Result(1.0f);
			Result[0][0] = 2.0f / (right - left);
			Result[1][1] = 2.0f / (top - bottom);
			Result[2][2] = -1.0f;
			Result[3][0] = -(right + left) / (right - left);
			Result[3][1] = -(top + bottom) / (top - bottom);
			return Result;
		}

		static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			Mat4 Result(1.0f);
			Result[0][0] = 2 / (right - left);
			Result[1][1] = 2 / (top - bottom);
			Result[2][2] = -2 / (zFar - zNear);
			Result[3][0] = -(right + left) / (right - left);
			Result[3][1] = -(top + bottom) / (top - bottom);
			Result[3][2] = -(zFar + zNear) / (zFar - zNear);
			return Result;
		}


		static Mat4 perspective(float fovy, float aspect, float zNear, float zFar)
		{
			float const tanHalfFovy = tan(fovy / 2);

			Mat4 Result(0);
			Result[0][0] = 1 / (aspect * tanHalfFovy);
			Result[1][1] = 1 / (tanHalfFovy);
			Result[2][2] = -(zFar + zNear) / (zFar - zNear);
			Result[2][3] = (2 * zFar * zNear) / (zNear - zFar);
			Result[3][2] = -1;
			return Result;
		}
	}
}