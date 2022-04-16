#pragma once
#include "ProEngine/Math/Vec2.h"
#include "SpriteSheet.h"
#include "../vendor/json/single_include/nlohmann/json.hpp"


namespace Pro
{
	class SpriteSheet;

	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(std::string name, Vec2 index, Vec2 dim, Ref<SpriteSheet> spriteSheet);

		Vec2& GetPos() { return m_pos; };
		Vec2& GetDim() { return m_dim; };
		Vec2& GetSize() { return m_size; };
		Vec2& GetIndex() { return m_index; };
		Vec2& GetCellSize() { return m_cellSize; };
		Ref<SpriteSheet> GetSpriteSheet() { return m_spriteSheet; };
		
		void SetPos(Vec2 pos) { m_pos = pos; };
		void SetDim(Vec2 dim) { m_dim = dim; };
		void SetSize(Vec2 size) { m_size = size; };

		const std::string GetName() { return m_name; };
		

		nlohmann::json Serialize();

		static Ref<Sprite> Create(std::string name, Vec2 pos, Vec2 dim, Ref<SpriteSheet> spriteSheet);


	private:
		std::string m_name;
		Vec2 m_cellSize;
		Vec2 m_index;
		Vec2 m_size;	// Dimension in pixel coords

		Vec2 m_pos;		// Position in img coords (0,1) interval
		Vec2 m_dim;		// Dimesion in img coords (0,1) interval
		Ref<SpriteSheet> m_spriteSheet;
	};

	
}

