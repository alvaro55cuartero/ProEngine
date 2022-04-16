#pragma once
#include "ProEngine/File/PPM/PPMFile.h"
#include <ProEngine/Types/Color.h>

namespace Pro 
{

	enum PixelGlyphFlags : uint8_t
	{
		None = 0,
		CornerTopLeft = 1,
		CornerTopRight = 2,
		CornerBottomLeft = 4,
		CornerBottomRight = 8,


		CornerTop = CornerTopLeft ^ CornerTopRight,
		CornerBottom = CornerBottomLeft ^ CornerBottomRight
	};

	struct PixelGlyphFormat
	{
		uint8_t m_width;
		uint8_t m_height;
		uint8_t m_middleHeight;
		uint8_t m_leftLegSize;
		uint8_t m_rightLegSize;

		Color m_color;

		PixelGlyphFlags m_flags;

		PixelGlyphFormat(const uint8_t& width = 5, const uint8_t& height = 7, const uint8_t& middleHeight = 3, const uint8_t& leftLegSize = 1, const uint8_t& rightLegSize = 1, const Color& color = Color(255,255,255), const PixelGlyphFlags& flags = PixelGlyphFlags::None)
			: m_width(width), m_height(height), m_middleHeight(middleHeight), m_leftLegSize(leftLegSize), m_rightLegSize(rightLegSize), m_color(color), m_flags(flags)
		{}
	};

	class PixelGlyph
	{

	public:
		PixelGlyph(PixelGlyphFormat format);

		PPMFile GetPPMFormatString();
		uint32_t* GetRawData() { return (uint32_t*)m_data; };
		uint32_t GetWidth() { return m_width; };
		uint32_t GetHeight() { return m_height; };

	private:
		void DrawCorners(const Vec2& pos, const bool& topLeft, const bool& topRight, const bool& bottomLeft, const bool& bottomRight);
		
		void GenA(const Vec2& pos, const Vec2& size);
		void GenB(const Vec2& pos, const Vec2& size);
		void GenC(const Vec2& pos, const Vec2& size);
		void GenD(const Vec2& pos, const Vec2& size);


	private:
		uint32_t m_width;
		uint32_t m_height;
		PixelGlyphFormat m_format;
		Color* m_data;

	};
}