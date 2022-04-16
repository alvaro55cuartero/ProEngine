#pragma once
#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Scene/Scene.h"
#include "ProEngine/ECS/Entity/Entity.h"

namespace Pro {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		void SetEntity(Entity entity) { m_entity = entity; };

		template<typename T>
		T& GetComponent()
		{
			return m_entity.GetComponent<T>();
		}

		Registry* GetRegistry() { return m_entity.GetRegistry(); }

	public:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_entity;
	};

}