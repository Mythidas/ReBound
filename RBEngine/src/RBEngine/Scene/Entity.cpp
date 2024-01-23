#include "rbpch.h"
#include "Entity.h"
#include "SceneManager.h"

namespace RB
{
	Entity::Entity(const EntityID& id)
		: m_ID(id), m_Registry(&SceneManager::GetActive()->GetRegistry())
	{
	}

	Entity::Entity(const EntityEntry& entry)
		: m_ID(entry.ID), m_Registry(entry.Registry)
	{
	}

	Entity::Entity(const EntityID& id, SceneRegistry& registry)
		: m_ID(id), m_Registry(&registry)
	{
	}

	Entity Entity::CreateDir()
	{
		return SceneManager::GetActive()->GetRegistry().CreateEntity();
	}

	Entity Entity::CreateDir(const std::string& name)
	{
		return SceneManager::GetActive()->GetRegistry().CreateEntity(name);
	}
}