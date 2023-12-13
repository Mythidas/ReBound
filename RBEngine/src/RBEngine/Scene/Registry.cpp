#include "rbpch.h"
#include "Registry.h"

namespace RB
{
	Registry::Registry()
		: m_EntityIndex(0)
	{
		m_Entities = new Entity[MAX_ENTITIES];
	}

	Registry::~Registry()
	{
		delete[] m_Entities;
	}

	EntityID Registry::CreateEntity()
	{
		if (!m_FreeEntities.empty())
		{
			EntityID oldID = m_FreeEntities.back();
			m_FreeEntities.pop_back();

			m_Entities[GetEntityIndex(oldID)].Components.reset();
			m_Entities[GetEntityIndex(oldID)].ID = GetEntityID(GetEntityIndex(oldID), GetEntityVersion(oldID) + 1);
			return m_Entities[GetEntityIndex(oldID)].ID;
		}
		else
		{
			m_Entities[m_EntityIndex].Components.reset();
			m_Entities[m_EntityIndex].ID = GetEntityID(m_EntityIndex, 0);
			m_EntityIndex++;
			return m_Entities[m_EntityIndex - 1].ID;
		}
	}

	void Registry::DestroyEntity(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return;

		m_FreeEntities.push_back(entity);
		m_Entities[GetEntityIndex(entity)].ID = GetEntityID(GetEntityIndex(entity), UINT32_MAX);
	}

	bool Registry::IsValidEntity(EntityID entity)
	{
		return GetEntityVersion(entity) != UINT32_MAX && GetEntityVersion(m_Entities[GetEntityIndex(entity)].ID) == GetEntityVersion(entity);
	}

	EntityID Registry::GetEntityID(EntityIndex index, EntityVersion version)
	{
		return EntityID((EntityID(index) << 32) | version);
	}

	EntityIndex Registry::GetEntityIndex(EntityID id)
	{
		return EntityIndex(id >> 32);
	}

	EntityVersion Registry::GetEntityVersion(EntityID id)
	{
		return EntityVersion(id);
	}
}