#include "Propch.h"
#include "SpriteSheet.h"

namespace Pro
{
	Ref<SpriteSheet> SpriteSheet::Create(std::string name, const std::string& path, const Pro::Ref<Pro::Texture2D>& texture, Pro::Vec2 gridSize)
	{
		return CreateRef<SpriteSheet>(name, path, texture, gridSize);
	}

	Ref<SpriteSheet> SpriteSheet::Create(std::string name, const std::string& path, Vec2 gridSize)
	{
		return CreateRef<SpriteSheet>(name, path, Pro::Texture2D::Create(path), gridSize);
	}

	Ref<SpriteSheet> SpriteSheet::Create(std::string name, const std::string& path, Vec2 gridSize, std::vector<Pro::Ref<Pro::Sprite>> sprites)
	{
		return CreateRef<SpriteSheet>(name, path, Pro::Texture2D::Create(path), gridSize, sprites);
	}

	Ref<SpriteSheet> SpriteSheet::Deserialize(const nlohmann::json& json)
	{
		std::string imgPath = json["path"].get<std::string>();
		std::string name = json["name"].get<std::string>();

		Vec2 gridSize = Pro::Vec2(json["gridSize"]["x"].get<float>(), json["gridSize"]["y"].get<float>());

		Pro::Ref<Pro::SpriteSheet> spriteSheet = CreateRef<SpriteSheet>(name, imgPath, Pro::Texture2D::Create(imgPath), gridSize);
		
		std::vector<Pro::Ref<Pro::Sprite>> sprites;
		for (auto& sprite: json["sprites"])
		{
			std::string name = sprite["name"].get<std::string>();
			Pro::Vec2 position = Pro::Vec2(sprite["position"]["x"].get<float>(), sprite["position"]["y"].get<float>());
			Pro::Vec2 dimension = Pro::Vec2(sprite["dimension"]["x"].get<float>(), sprite["dimension"]["y"].get<float>());

			sprites.push_back(Pro::Sprite::Create(name, position, dimension, spriteSheet));
		}
		spriteSheet->SetSprites(sprites);

		return spriteSheet;
	}

	nlohmann::json SpriteSheet::Serialize()
	{
		nlohmann::json json = {
			{"name", m_name},
			{"path", m_path},
			{"gridSize", {
				{"x", m_gridSize.x},
				{"y", m_gridSize.y},
			}},
			{"sprites", {}}
		};

		for (auto& sprite : m_sprites) {
			json["sprites"].push_back(sprite->Serialize());
		}

		return json;
	}


	void SpriteSheet::AddSprites(std::vector<Pro::Ref<Pro::Sprite>> sprites)
	{

	}
	void SpriteSheet::SetSprites(std::vector<Pro::Ref<Pro::Sprite>> sprites)
	{
		m_sprites = sprites;
	}


	void SpriteSheet::Bind(uint32_t slot)
	{
		m_texture->Bind(slot);
	}
}