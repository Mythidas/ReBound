#include "rbpch.h"
#include "EntityRegistry.h"
#include "Entity.h"
#include "Transform.h"
#include "Tag.h"
#include "RBEngine/Reflection/Domain.h"

namespace RB
{
	EntityRegistry::EntityRegistry()
		: m_EntityIndex(0)
	{
		m_Entities = new EntityEntry[MAX_ENTITIES]{};
	}

	EntityRegistry::~EntityRegistry()
	{
		delete[] m_Entities;
	}

	Entity EntityRegistry::CreateEntity()
	{
		return CreateEntity("Empty Entity");
	}

	Entity EntityRegistry::CreateEntity(const std::string& name)
	{
		if (!m_FreeEntities.empty())
		{
			EntityID oldID = m_FreeEntities.back();
			m_FreeEntities.pop_back();

			m_Entities[GetEntityIndex(oldID)].Components.reset();
			m_Entities[GetEntityIndex(oldID)].ID = GetEntityID(GetEntityIndex(oldID), GetEntityVersion(oldID) + 1);
			m_Entities[GetEntityIndex(oldID)].Registry = this;
			AddComponent<Tag>(m_Entities[GetEntityIndex(oldID)].ID)->Name = name;
			AddComponent<Transform>(m_Entities[GetEntityIndex(oldID)].ID);
			return m_Entities[GetEntityIndex(oldID)];
		}
		else
		{
			m_Entities[m_EntityIndex].Components.reset();
			m_Entities[m_EntityIndex].ID = GetEntityID(m_EntityIndex, 0);
			m_Entities[m_EntityIndex].Registry = this;
			AddComponent<Tag>(m_Entities[m_EntityIndex].ID)->Name = name;
			AddComponent<Transform>(m_Entities[m_EntityIndex].ID);

			m_EntityIndex++;
			return m_Entities[m_EntityIndex - 1];
		}
	}

	void EntityRegistry::DestroyEntity(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return;

		m_FreeEntities.push_back(entity);
		m_Entities[GetEntityIndex(entity)].ID = GetEntityID(GetEntityIndex(entity), UINT32_MAX);
	}

	void EntityRegistry::AddComponent(const EntityID& entity, const TypeID& component)
	{
		Domain::FindComponent(component).AddFunc(entity);
	}

	void* EntityRegistry::GetComponent(const EntityID& entity, const TypeID& component)
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID(component);

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return (void*)(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		return nullptr;
	}

	bool EntityRegistry::HasComponent(const EntityID& entity, const TypeID& component)
	{
		if (!IsValidEntity(entity)) return false;

		size_t compID = FindComponentID(component);

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return true;

		return false;
	}

	void EntityRegistry::RemoveComponent(const EntityID& entity, const TypeID& component)
	{
		if (!IsValidEntity(entity)) return;

		size_t compID = FindComponentID(component);
		m_Entities[GetEntityIndex(entity)].Components.reset(compID);
	}

	std::vector<ComponentMeta> EntityRegistry::GetComponents(const EntityID& entity) const
	{
		if (!IsValidEntity(entity)) return std::vector<ComponentMeta>();

		std::vector<ComponentMeta> components;
		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			if (m_Entities[GetEntityIndex(entity)].Components.test(i))
				components.push_back(Domain::FindComponent(m_ComponentPools[i]->GetType()));
		}

		return components;
	}

	size_t EntityRegistry::FindComponentID(const TypeID& component) const
	{
		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			if (m_ComponentPools[i]->IsType(component))
				return i;
		}

		return m_ComponentPools.size();
	}

	bool EntityRegistry::IsValidEntity(EntityID entity) const
	{
		return GetEntityVersion(entity) != UINT32_MAX && GetEntityVersion(m_Entities[GetEntityIndex(entity)].ID) == GetEntityVersion(entity);
	}

	EntityID EntityRegistry::GetEntityID(EntityIndex index, EntityVersion version) const
	{
		return EntityID((EntityID(index) << 32) | version);
	}

	EntityIndex EntityRegistry::GetEntityIndex(EntityID id) const
	{
		return EntityIndex(id >> 32);
	}

	EntityVersion EntityRegistry::GetEntityVersion(EntityID id) const
	{
		return EntityVersion(id);
	}
}