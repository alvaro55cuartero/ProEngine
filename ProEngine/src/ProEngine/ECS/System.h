#pragma once
#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Renderer/Renderer2D.h"
#include "ProEngine/ECS/Registry/Registry.h"
#include "ProEngine/Renderer/Sprite/SpriteLibrary.h"

namespace Pro
{

	class System
	{
	public:
		virtual void Execute(Registry* registry, Timestep delta) = 0;
	};

	class Renderer2DSystem : public System
	{
	public:
		Renderer2DSystem() = default;
		Renderer2DSystem(SpriteLibrary* spriteLibrary)
			: m_spriteLibrary(spriteLibrary)
		{
			m_renderer.Init();
		}
		
		void Execute(Registry* registry, Timestep delta) override;

	private:
		Camera* m_cam = nullptr;
		SpriteLibrary* m_spriteLibrary = nullptr;
		Renderer2D m_renderer;
	};


	class NativeScriptSystem : public System
	{
	public:
		NativeScriptSystem() = default;
		
		void Execute(Pro::Registry* registry, Timestep delta) override;

	};

	class Physisc2DSystem : public System
	{
	public:
		Physisc2DSystem() = default;

		void Execute(Pro::Registry* registry, Timestep delta) override;

	};

	class ColliderRenderer2DSystem : public System
	{
	public:
		ColliderRenderer2DSystem()
		{
			m_renderer.Init();

			Pro::Ref<Pro::Texture2D> texture = Pro::Texture2D::Create(1, 1);
			uint32_t textureData = 0xffffffff;
			texture->SetData(&textureData, sizeof(uint32_t));
			auto whiteTexture = Pro::SpriteSheet::Create("White", "", texture, { 1,1 });

			sprite = Pro::Sprite::Create("FULL", { 1, 1 }, { 32, 32 }, whiteTexture);
		}

		void Execute(Pro::Registry* registry, Timestep delta) override;
		
	private:
		Camera* m_cam = nullptr;
		Renderer2D m_renderer;
		Ref<Sprite> sprite;
	};

}
