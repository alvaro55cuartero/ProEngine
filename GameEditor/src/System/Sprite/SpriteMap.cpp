#include "SpriteMap.h"

void SpriteMap::AddLayer(uint32_t z)
{
	if (z >= m_indices.size())
		m_indices.resize(z + 1);

	m_indices[z] = (uint32_t)m_layers.size();
	m_layers.push_back(SpriteLayer((float)z));
}

void SpriteMap::AddTile(Pro::Vec2 pos)
{
	
}

SpriteLayer SpriteMap::GetLayer(uint32_t z)
{
	return m_layers[m_indices[z]];
}
