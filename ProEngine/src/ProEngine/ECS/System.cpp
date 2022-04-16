#include "Propch.h"
#include "System.h"
#include "Component.h"

namespace Pro
{
	void Renderer2DSystem::Execute(Registry* reg, Timestep delta)
	{
		PRO_PROFILE_FUNCTION();

		{
			PRO_PROFILE_SCOPE("Setting Camera");
			auto view = reg->GetView<CameraComponent>();
			for (auto entity : view)
			{
				auto camera = reg->Get<CameraComponent>(entity);
				if (camera.Primary)
				{
					m_cam = camera.Camera;
				}
			}
		}

		
		if (m_cam) {
			PRO_PROFILE_SCOPE("Rendereing 2D");

			auto view = reg->GetView<TransformComponent, SpriteComponent>();

			for (auto entity : view)
			{
				TransformComponent transform = reg->Get<TransformComponent>(entity);
				SpriteComponent sprite = reg->Get<SpriteComponent>(entity);
				if (sprite.Sprite == "") continue;
				if (!m_spriteLibrary->Exists(sprite.Sprite)) continue;
		
				m_renderer.AddSquare(transform.Translation, transform.Scale, sprite.Color, m_spriteLibrary->Get(sprite.Sprite));
			}
	
			m_renderer.Render(*m_cam);
		}
	}

	void NativeScriptSystem::Execute(Registry* reg, Timestep delta)
	{
		PRO_PROFILE_FUNCTION();

		auto view = reg->GetView<NativeScriptComponent>();

		for (auto entity : view)
		{
			Pro::NativeScriptComponent& script = reg->Get<Pro::NativeScriptComponent>(entity);

			if (!script.Instance)
			{
				script.Instance = script.InstantiateScript();
				script.Instance->SetEntity(Pro::Entity(entity, reg));
				script.Instance->OnCreate();
			}

			script.Instance->OnUpdate(delta);
		}
	}

	void Physisc2DSystem::Execute(Pro::Registry* reg, Timestep delta)
	{
		auto view = reg->GetView<BoxCollider2DComponent>();


	}

	void ColliderRenderer2DSystem::Execute(Pro::Registry* reg, Timestep delta)
	{
		PRO_PROFILE_FUNCTION();

		{
			PRO_PROFILE_SCOPE("Setting Camera");
			auto view = reg->GetView<CameraComponent>();
			for (auto entity : view)
			{
				auto camera = reg->Get<CameraComponent>(entity);
				if (camera.Primary)
				{
					m_cam = camera.Camera;
				}
			}
		}


		if (m_cam) {
			PRO_PROFILE_SCOPE("Rendereing 2D");

			auto view = reg->GetView<TransformComponent, BoxCollider2DComponent>();

			for (auto entity : view)
			{
				TransformComponent transform = reg->Get<TransformComponent>(entity);
				BoxCollider2DComponent collider = reg->Get<BoxCollider2DComponent>(entity);

				m_renderer.AddSquare(transform.Translation, transform.Scale, {1,1,1,1}, sprite);
			}

			m_renderer.Render(*m_cam);
		}
	}


}