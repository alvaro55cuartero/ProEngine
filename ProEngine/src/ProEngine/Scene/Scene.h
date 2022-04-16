#pragma once

#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Renderer/Renderer2D.h"
#include "ProEngine/Renderer/Renderer3D.h"
#include "ProEngine/ECS/Entity/Entity.h"
#include "ProEngine/ECS/Component.h"
#include "ProEngine/ECS/System.h"
#include "ProEngine/ECS/Registry/Registry.h"
#include "ProEngine/Renderer/Cameras/PixelPerfectCamera.h"

namespace Pro
{
	class Entity;

	class Scene
	{
	public:
		Scene(Registry* reg);

		~Scene();

		void OnUpdate(Timestep delta);

		Entity CreateEntity(const std::string& name);
		bool HasEntity(const std::string& name);
		Entity GetEntity(const std::string& name);

		void AddSystem(System* system);

		void Load(std::string path);
		void Save(std::string path);
	private:
		SpriteLibrary m_spriteLibrary;
		Registry* m_reg;
		std::vector<System*> m_systems;
	};
}