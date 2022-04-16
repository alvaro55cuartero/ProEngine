#include "Propch.h"
#include "PPMFile.h"

namespace Pro {

	PPMFile::PPMFile(const uint32_t& width, const uint32_t& height, Color* data)
		:m_width(width), m_height(height), m_data(data)
	{
		m_magicNumber = "P3";
		m_maxVal = 255;
	}

	std::string PPMFile::GetFileAsText()
	{
		std::ostringstream os;
		os << m_magicNumber << "\n"
			<< m_width << " "
			<< m_height << "\n"
			<< m_maxVal << "\n";

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++) 
			{
				Color& a = m_data[i * m_width + j];

				os <<  a.r << " " << a.g << " " << a.b << " ";
			}
			os << "\n";
		}

		return os.str();
	}

	void PPMFile::AddSquare(const Vec2& pos, const Vec2& size, Color* data) 
	{
		for (int i = 0; i < size.y; i++) {
			for (int j = 0; j < size.x; j++) {
				m_data[((int)pos.y + i) * m_width + j + (int)pos.x] = data[i * (int)size.x + j];
			}
		}
	}


}