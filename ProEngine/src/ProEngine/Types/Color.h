#pragma once
#include <cstdint>

namespace Pro
{
	struct Color
	{
		Color()
			:r(0), g(0), b(0), a(0)
		{}

		Color(const uint16_t& r, const uint16_t& g, const uint16_t& b)
			: r(r), g(g), b(b), a(0)
		{}

		Color(const uint16_t& r, const uint16_t& g, const uint16_t& b, const uint16_t& a)
			: r(r), g(g), b(b), a(a)
		{}

	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t a;
	};
}