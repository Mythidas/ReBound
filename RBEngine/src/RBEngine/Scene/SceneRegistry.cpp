#include "rbpch.h"
#include "SceneRegistry.h"
#include "Entity.h"
#include "Transform.h"
#include "Tag.h"
#include "RBEngine/Reflection/Domain.h"

namespace RB
{
	SceneRegistry::SceneRegistry()
		: m_EntityIndex(0)
	{
		m_Entities = new EntityEntry[MAX_ENTITIES]{};
	}

	SceneRegistry::~SceneRegistry()
	{
		delete[] m_Entities;
		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			delete m_ComponentPools[i];
		}
	}

	Entity SceneRegistry::CreateEntity()
	{
		return CreateEntity("Empty Entity");
	}

	Entity SceneRegistry::CreateEntity(const std::string& name)
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

	void SceneRegistry::DestroyEntity(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return;

		m_FreeEntities.push_back(entity);
		m_Entities[GetEntityIndex(entity)].ID = GetEntityID(GetEntityIndex(entity), UINT32_MAX);
	}

	void SceneRegistry::AddComponent(const EntityID& entity, const TypeID& component)
	{
		Domain::FindComponent(component).AddFunc(this, entity);
	}

	void* SceneRegistry::GetComponent(const EntityID& entity, const TypeID& component) const
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID(component);

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return (void*)(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		return nullptr;
	}

	bool SceneRegistry::HasComponent(const EntityID& entity, const TypeID& component) const
	{
		if (!IsValidEntity(entity)) return false;

		size_t compID = FindComponentID(component);

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return true;

		return false;
	}

	void SceneRegistry::RemoveComponent(const EntityID& entity, const TypeID& component)
	{
		if (!IsValidEntity(entity)) return;

		size_t compID = FindComponentID(component);
		m_Entities[GetEntityIndex(entity)].Components.reset(compID);
	}

	std::vector<ComponentMeta> SceneRegistry::GetComponents(const EntityID& entity) const
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

	size_t SceneRegistry::FindComponentID(const TypeID& component) const
	{
		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			if (m_ComponentPools[i]->IsType(component))
				return i;
		}

		return m_ComponentPools.size();
	}

	bool SceneRegistry::IsValidEntity(EntityID entity) const
	{
		return GetEntityVersion(entity) != UINT32_MAX && GetEntityVersion(m_Entities[GetEntityIndex(entity)].ID) == GetEntityVersion(entity);
	}

	EntityID SceneRegistry::GetEntityID(EntityIndex index, EntityVersion version) const
	{
		return EntityID((EntityID(index) << 32) | version);
	}

	EntityIndex SceneRegistry::GetEntityIndex(EntityID id) const
	{
		return EntityIndex(id >> 32);
	}

	EntityVersion SceneRegistry::GetEntityVersion(EntityID id) const
	{
		return EntityVersion(id);
	}
}