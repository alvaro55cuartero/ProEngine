#pragma once
#include <map>
#include "../vendor/json/single_include/nlohmann/json.hpp"
#include "ProEngine/Renderer/Texture.h"
#include "Sprite.h"
#include "ProEngine/File/File.h"

namespace Pro
{
	class Sprite;
	class SpriteSheet
	{

	public:
		SpriteSheet(std::string name, std::string path, Ref<Texture2D> texture, Vec2 gridSize, std::vector<Pro::Ref<Pro::Sprite>> sprites = {})
			:m_name(name),m_path(path), m_texture(texture), m_gridSize(gridSize), m_sprites(sprites)
		{
		}

		void Bind(uint32_t slot = 0);

		void AddSprites(std::vector<Pro::Ref<Pro::Sprite>> sprites);
		void SetSprites(std::vector<Pro::Ref<Pro::Sprite>> sprites);

		Vec2 GetGridSize() { return m_gridSize; }

		Vec2 GetTextureSize() { return { (float)m_texture->GetWidth(), (float)m_texture->GetHeight() }; }
		uint32_t GetWidth() { return m_texture->GetWidth(); }
		uint32_t GetHeight() { return m_texture->GetHeight(); }
		std::vector<Pro::Ref<Pro::Sprite>> GetSprites() { return m_sprites; }

		nlohmann::json Serialize();

		std::string GetName() { return m_name; }
	public:
		static Ref<SpriteSheet> Create(std::string name, const std::string& path, Vec2 gridSize);
		static Ref<SpriteSheet> Create(std::string name, const std::string& path, Vec2 gridSize, std::vector<Pro::Ref<Pro::Sprite>> sprites);
		static Ref<SpriteSheet> Create(std::string name, const std::string& path, const Ref<Texture2D>& texture, Vec2 gridSize);
		static Ref<SpriteSheet> Deserialize(const nlohmann::json& json);


	private:
		std::string m_name;
		std::string m_path;
		Vec2 m_gridSize;
		Ref<Texture2D> m_texture;
		std::vector<Pro::Ref<Pro::Sprite>> m_sprites;
	};

}

