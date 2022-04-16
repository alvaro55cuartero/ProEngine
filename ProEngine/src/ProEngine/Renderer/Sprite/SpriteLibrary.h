#pragma once
#include "Sprite.h"
#include "../vendor/json/single_include/nlohmann/json.hpp"

namespace Pro
{
	class SpriteLibrary
	{

	public:
		SpriteLibrary() = default;

		void Add(const std::string& name, const Ref<Sprite>& sprite);
		void Add(const Ref<Sprite>& sprite);
		void Add(const Ref<SpriteSheet>& spriteSheet);;

		Ref<Sprite> Get(const std::string& name);


		bool Exists(const std::string& name) const;

		nlohmann::json Serialize();

		void Deserialize(nlohmann::json json);
	private:
		std::vector<Ref<SpriteSheet>> m_spriteSheets;
		std::unordered_map<std::string, Ref<Sprite>> m_sprites;
	};
};

