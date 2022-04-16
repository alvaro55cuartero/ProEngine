#include "Propch.h"
#include "SpriteLibrary.h"


namespace Pro
{

	void SpriteLibrary::Add(const Ref<Sprite>& sprite)
	{
		auto& name = sprite->GetName();
		Add(name, sprite);
	}

	void SpriteLibrary::Add(const Ref<SpriteSheet>& spriteSheet)
	{
		m_spriteSheets.push_back(spriteSheet);
		for (auto& sprite : spriteSheet->GetSprites())
		{
			Add(sprite);
		}
	}

	void SpriteLibrary::Add(const std::string& name, const Ref<Sprite>& sprite)
	{
		//PRO_CORE_ASSERT(!Exists(name), "Sprite already exists!");
		m_sprites[name] = sprite;
	}


	Ref<Sprite> SpriteLibrary::Get(const std::string& name)
	{
		//PRO_CORE_ASSERT(Exists(name), "Sprite not found!");
		return m_sprites[name];
	}

	bool SpriteLibrary::Exists(const std::string& name) const
	{
		return m_sprites.find(name) != m_sprites.end();
	}

	nlohmann::json SpriteLibrary::Serialize()
	{
		nlohmann::json json;
		for (auto& spriteSheet : m_spriteSheets)
		{
			json.push_back(spriteSheet->Serialize());
		}

		return json;
	}

	void SpriteLibrary::Deserialize(nlohmann::json json)
	{
		for (auto& spriteSheet : json)
		{
			Pro::Ref<Pro::SpriteSheet> ss = Pro::SpriteSheet::Deserialize(spriteSheet);
			Add(ss);
		}
	}

}