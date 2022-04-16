#include "Propch.h"
#include "Sprite.h"

namespace Pro
{
	Sprite::Sprite(std::string name, Vec2 index, Vec2 cellSize, Ref<SpriteSheet> spriteSheet) : m_name(name), m_spriteSheet(spriteSheet)
	{
		m_cellSize = cellSize;
		m_index = index;
		m_pos = index * spriteSheet->GetGridSize() / spriteSheet->GetTextureSize();
		m_size = cellSize * spriteSheet->GetGridSize();
		m_dim = m_pos + m_size / spriteSheet->GetTextureSize();
	};

	Ref<Sprite> Sprite::Create(std::string name, Vec2 pos, Vec2 dim, Ref<SpriteSheet> spriteSheet)
	{
		return CreateRef<Sprite>(name, pos, dim, spriteSheet);
	}


	nlohmann::json Sprite::Serialize()
	{
		nlohmann::json json;

		json["name"] = GetName();
		json["position"] = {
			{ "x", GetIndex().x},
			{ "y", GetIndex().y}
		};

		json["dimension"] = {
			{ "x", GetCellSize().x},
			{ "y", GetCellSize().y}
		};
		return json;
	}




}