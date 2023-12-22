#include "rbpch.h"
#include "Entity.h"
#include "Scene.h"

namespace RB
{
	Entity::Entity(const EntityID& id)
		: m_ID(id), m_Registry(&Scene::GetActive()->GetRegistry())
	{
	}

	Entity::Entity(const EntityEntry& entry)
		: m_ID(entry.ID), m_Registry(entry.Registry)
	{
	}

	Entity::Entity(const EntityID& id, EntityRegistry& registry)
		: m_ID(id), m_Registry(&registry)
	{
	}

	Entity Entity::Create()
	{
		return Scene::GetActive()->GetRegistry().CreateEntity();
	}

	Entity Entity::Create(const std::string& name)
	{
		return Scene::GetActive()->GetRegistry().CreateEntity(name);
	}
}