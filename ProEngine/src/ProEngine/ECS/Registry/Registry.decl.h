#pragma once
#include "ProEngine/Containers/SparseMap.h"
#include "ProEngine/ECS/Entity/Entity.forward.h"
#include "ProEngine/ECS/Registry/Registry.forward.h"

namespace Pro
{
	class Registry : public SparseMap
	{
	public:
		Entity CreateEntity();

		uint32_t GetCount();

	private:
		uint32_t m_entityCount = 0;

	};
}