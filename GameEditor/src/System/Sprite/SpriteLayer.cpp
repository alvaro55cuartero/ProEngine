#include "SpriteLayer.h"


void SpriteLayer::AddSprite(Pro::Vec2 pos, Pro::Vec4 color, uint32_t textIndex, Pro::Ref<Pro::Sprite> sprite)
{
	m_mesh.AddSquare(pos, sprite->GetSize(), color, (float)textIndex, sprite);
}

