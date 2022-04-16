#pragma once
#include "ProEngine.h"

class SpriteLayer
{
public:
	SpriteLayer(float layer) 
		: m_layer(layer)
	{}

	void AddSprite(Pro::Vec2 pos, Pro::Vec4 color, uint32_t textIndex, Pro::Ref<Pro::Sprite> sprite);


	float GetLayer()
	{
		return m_layer;
	}

private:

	float m_layer;
	Pro::Mesh m_mesh;
};