#include "Propch.h"
#include "Registry.h"

namespace Pro
{
	uint32_t Registry::GetCount()
	{
		return m_entityCount;
	}

	Entity Registry::CreateEntity()
	{
		return Entity(m_entityCount++, this);
	}
}