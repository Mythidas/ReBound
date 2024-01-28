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

	bool Entity::IsActive() const
	{
		if (!m_Registry) return false;
		Tag* tag = m_Registry->GetComponent<Tag>(*this);
		return !tag || !tag->Active;
	}

	Entity Entity::Create()
	{
		return SceneManager::GetActive()->GetRegistry().CreateEntity();
	}

	Entity Entity::Create(const std::string& name)
	{
		return SceneManager::GetActive()->GetRegistry().CreateEntity(name);
	}
}