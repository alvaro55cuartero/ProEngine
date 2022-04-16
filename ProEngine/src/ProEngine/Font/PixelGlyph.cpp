#include "Propch.h"
#include "PixelGlyph.h"

namespace Pro 
{

	PixelGlyph::PixelGlyph(PixelGlyphFormat format)
		: m_format(format), m_width(100), m_height(100), m_data(new Color[100 * 100])
	{
		std::fill_n(m_data, m_width * m_height, Color());
		GenA({ 1,1 }, Vec2(m_format.m_width, m_format.m_height));
		GenB(Vec2(2 + m_format.m_width, 1), Vec2(m_format.m_width, m_format.m_height));
		GenC(Vec2(3 + m_format.m_width * 2, 1), Vec2(m_format.m_width, m_format.m_height));

	}

	PPMFile PixelGlyph::GetPPMFormatString()
	{
		PPMFile file(100, 100, m_data);

		return file;
	}

	void PixelGlyph::DrawCorners(const Vec2& pos, const bool& topLeft, const bool& topRight, const bool& bottomLeft, const bool& bottomRight)
	{
		Color black;
		if (topLeft && (m_format.m_flags & PixelGlyphFlags::CornerTopLeft) != PixelGlyphFlags::CornerTopLeft)
			m_data[(int)pos.y * m_width + (int)pos.x] = black;

		if (topRight && (m_format.m_flags & PixelGlyphFlags::CornerTopRight) != PixelGlyphFlags::CornerTopRight)
			m_data[(int)pos.y * m_width + (int)pos.x + (int)m_format.m_width - 1] = black;

		if (bottomLeft && (m_format.m_flags & PixelGlyphFlags::CornerBottomLeft) != PixelGlyphFlags::CornerBottomLeft)
			m_data[(m_format.m_height + (int)pos.y - 1) * m_width + (int)pos.x ] = black;

		if (bottomRight && (m_format.m_flags & PixelGlyphFlags::CornerBottomRight) != PixelGlyphFlags::CornerBottomRight)
			m_data[(m_format.m_height + (int)pos.y - 1) * m_width + (int)pos.x + (int)m_format.m_width - 1] = black;
	}


	void PixelGlyph::GenA(const Vec2& pos, const Vec2& size)
	{
		Color black;
		for (uint8_t i = 0; i < size.y; i++) {
			for (uint8_t j = 0; j < size.x; j++) {
				const uint8_t& x = j + pos.x;
				const uint8_t& y = i + pos.y;

				m_data[y * m_width + x] = (i == 0 || i == m_format.m_middleHeight || j == 0 || j == size.x - 1) ? m_format.m_color : black;
			}
		}

		DrawCorners(pos, true, true, false, false);
	}

	void PixelGlyph::GenB(const Vec2& pos, const Vec2& size)
	{
		Color black;
		for (uint8_t i = 0; i < size.y; i++) {
			for (uint8_t j = 0; j < size.x; j++) {
				const uint8_t& x = j + pos.x;
				const uint8_t& y = i + pos.y;

				m_data[y * m_width + x] = (i == 0 || j == 0 || j == size.x - 1 || i == size.y - 1|| i == m_format.m_middleHeight) ? m_format.m_color : black;
			}
		}

		m_data[((int)pos.y + m_format.m_middleHeight) * m_width + (int)pos.x + m_format.m_width - 1] = black;

		DrawCorners(pos, true, true, true, true);
	}

	void PixelGlyph::GenC(const Vec2& pos, const Vec2& size)
	{
		Color black;
		for (uint8_t i = 0; i < size.y; i++) {
			for (uint8_t j = 0; j < size.x; j++) {
				const uint8_t& x = j + pos.x;
				const uint8_t& y = i + pos.y;

				m_data[y * m_width + x] = (i == 0 || j == 0 || i == size.y - 1 ) ? m_format.m_color : black;
			}
		}

		DrawCorners(pos, true, false, true, false);
	}

	void PixelGlyph::GenD(const Vec2& pos, const Vec2& size)
	{
		Color black;
		
		for (uint8_t i = 0; i < size.y; i++) {
			for (uint8_t j = 0; j < size.x; j++) {
				const uint8_t& x = j + pos.x;
				const uint8_t& y = i + pos.y;

				m_data[y * m_width + x] = (i == 0 || j == 0 || i == size.y - 1) ? m_format.m_color : black;
			}
		}

		DrawCorners(pos, true, false, true, false);
	}
}