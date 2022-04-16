#pragma once
#include "ProEngine/ECS/Entity/Entity.forward.h"
#include "ProEngine/ECS/Registry/Registry.forward.h"

namespace Pro
{

	class Entity
	{
	public:
		Entity() = default;
		Entity(uint32_t id, Registry* reg) : m_id(id), m_reg(reg) {};

		template<typename T> T& GetComponent();
		template<typename T, typename... Args> T& AddComponent(Args&&... args);
		Registry* GetRegistry() { return m_reg; };

		operator float() { return *((float*)&m_id); }
		operator int() { return *((int*)&m_id); }
		operator uint32_t() { return m_id; }

	private:
		uint32_t m_id;
		Registry* m_reg;

	};
}

