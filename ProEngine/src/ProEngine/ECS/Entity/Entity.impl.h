#pragma once
#include "ProEngine/ECS/Registry/Registry.decl.h"

namespace Pro
{
	template<typename T> T& Entity::GetComponent()
	{
		return m_reg->Get<T>(m_id);
	}

	template<typename T, typename... Args> T& Entity::AddComponent(Args&&... args)
	{
		T& component = m_reg->Emplace<T>(m_id, std::forward<Args>(args)...);
		return component;
	}
}