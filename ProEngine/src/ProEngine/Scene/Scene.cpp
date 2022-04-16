#include "Propch.h"
#include "ProEngine/Scene/Scene.h"


namespace Pro
{
	Scene::Scene(Registry* reg)
		: m_reg(reg)
	{
		//m_cam(Pro::PixelPerfectCamera(1280, 720))
		Load("../Game/assets/Json/entities.json");
		

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = m_reg->CreateEntity();
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);
		return entity;
	}

	bool Scene::HasEntity(const std::string& name)
	{
		auto view = m_reg->GetView<TagComponent>();
		for (auto entity : view)
		{
			auto tag = m_reg->Get<TagComponent>(entity);
			if (tag.Tag == name) {
				return true;
			}
		}

		return false;
	}

	Entity Scene::GetEntity(const std::string& name)
	{
		auto view = m_reg->GetView<TagComponent>();
		for (auto entity : view)
		{
			auto tag = m_reg->Get<TagComponent>(entity);
			if (tag.Tag == name) {
				return Entity(entity, m_reg);
			}
		}
	}




	void Scene::AddSystem(System* system)
	{
		m_systems.push_back(new Pro::NativeScriptSystem());
		m_systems.push_back(new Pro::Renderer2DSystem(&m_spriteLibrary));
		m_systems.push_back(new Pro::ColliderRenderer2DSystem());
	}

	void Scene::Load(std::string path)
	{
		// Load Textures
		{
			std::string data = Pro::File::Load("Assets/Json/Game_textures.json");
			nlohmann::json json = nlohmann::json::parse(data);
			m_spriteLibrary.Deserialize(json);
		}

		//Load Entities

		{
			std::string text = Pro::File::Load(path);

			nlohmann::json json = nlohmann::json::parse(text);

			for (auto data : json)
			{
				Pro::Entity entity = m_reg->CreateEntity();

				if (data.contains("Tag"))
				{
					m_reg->Emplace<Pro::TagComponent>(entity).Deserialize(data["Tag"]);
				}

				if (data.contains("Transform"))
				{
					m_reg->Emplace<Pro::TransformComponent>(entity).Deserialize(data["Transform"]);
				}

				if (data.contains("Sprite"))
				{
					m_reg->Emplace<Pro::SpriteComponent>(entity).Deserialize(data["Sprite"]);
				}

				if (data.contains("Camera"))
				{
					m_reg->Emplace<Pro::CameraComponent>(entity).Deserialize(data["Camera"]);
				}

				if (data.contains("BoxCollider2D"))
				{
					m_reg->Emplace<Pro::BoxCollider2DComponent>(entity).Deserialize(data["BoxCollider2D"]);
				}
			}
		}
	}
	
	void Scene::Save(std::string path)
	{
		nlohmann::json j;


		for (uint32_t i = 0; i < m_reg->GetCount(); i++)
		{

			if (m_reg->Has<Pro::TagComponent>(i))
			{
				Pro::TagComponent& tag = m_reg->Get<Pro::TagComponent>(i);
				j[i]["Tag"] = tag.Serialize();
			}

			if (m_reg->Has<Pro::CameraComponent>(i))
			{
				Pro::CameraComponent& cam = m_reg->Get<Pro::CameraComponent>(i);
				j[i]["Camera"] = cam.Serialize();
			}

			if (m_reg->Has<Pro::TransformComponent>(i))
			{
				Pro::TransformComponent& transform = m_reg->Get<Pro::TransformComponent>(i);
				j[i]["Transform"] = transform.Serialize();
			}

			if (m_reg->Has<Pro::SpriteComponent>(i))
			{
				Pro::SpriteComponent& sprite = m_reg->Get<Pro::SpriteComponent>(i);
				j[i]["Sprite"] = sprite.Serialize();
			}

			if (m_reg->Has<Pro::BoxCollider2DComponent>(i))
			{
				Pro::BoxCollider2DComponent& collider = m_reg->Get<Pro::BoxCollider2DComponent>(i);
				j[i]["BoxCollider2D"] = collider.Serialize();
			}
		}


		Pro::File::Save(j.dump(4), path);
	}

	void Scene::OnUpdate(Timestep delta)
	{

		for (auto system: m_systems)
		{
			system->Execute(m_reg, delta);
		}
	}
	
}