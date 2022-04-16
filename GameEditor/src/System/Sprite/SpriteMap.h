#pragma once

#include "SpriteLayer.h"
#include <vector>

class SpriteMap
{
public:
	void AddLayer(uint32_t z);
	void AddTile(Pro::Vec2 pos);
	SpriteLayer GetLayer(uint32_t z);

private:
	std::vector<uint32_t> m_indices;
	std::vector<SpriteLayer> m_layers;
};

