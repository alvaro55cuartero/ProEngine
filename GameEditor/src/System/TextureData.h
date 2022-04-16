#pragma once
#include "ProEngine.h"

class TextureData
{
public:

	TextureData(uint32_t width, uint32_t height, uint32_t component)
		: m_width(width), m_height(height), m_component(component)
	{
		imageData.resize(m_width * m_height * m_component);
		addData();
	}

	void addData()
	{

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				addData({(float)i, (float)j }, { 200, 100, 40, 255 });
			}
		}
	}

	void addData(Pro::Vec2 position, Pro::Vec4 color)
	{
		imageData[(uint32_t)position.x * m_width * m_component + (uint32_t)position.y * m_component + 0] = (char)color.x;
		imageData[(uint32_t)position.x * m_width * m_component + (uint32_t)position.y * m_component + 1] = (char)color.y;
		imageData[(uint32_t)position.x * m_width * m_component + (uint32_t)position.y * m_component + 2] = (char)color.z;
		imageData[(uint32_t)position.x * m_width * m_component + (uint32_t)position.y * m_component + 3] = (char)color.w;
	}

	void SavePNG(std::string path)
	{
		Pro::File::SavePNG(path, m_width, m_height, imageData.data(), m_component);
	}

	

private:
	const int m_width = 256;
	const int m_height = 256;
	const int m_component = 4;
	std::vector<char> imageData;

};