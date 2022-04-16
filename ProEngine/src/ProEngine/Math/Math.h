#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "Mat3.h"
#include "Mat4.h"

#include <cstdarg>
/*
namespace Pro 
{
	std::string format(const char* msg, ...)
	{
		std::size_t const STRING_BUFFER(4096);
		char text[STRING_BUFFER];
		va_list list;

		va_start(list, msg);
		vsprintf_s(text, STRING_BUFFER, msg, list);
		va_end(list);

		return std::string(text);
	}

	static std::string toString(const Vec4& v)
	{
		return format("vec4(%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w);
	}

	static std::string toString(const Mat4& m)
	{
		return format("Mat4:\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)",
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]
		);
	}
}*/
