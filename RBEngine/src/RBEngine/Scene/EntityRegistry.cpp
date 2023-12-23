#include "rbpch.h"
#include "EntityRegistry.h"
#include "Entity.h"
#include "ComponentFactory.h"
#include "SceneComps.h"
#include "RBEngine/Rendering/RenderComps.h"

namespace RB
{
	std::unordered_map<std::string, ComponentMeta> EntityRegistry::s_RegisteredComponents;

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

	void EntityRegistry::AddComponent(const std::string& component, const EntityID& entity)
	{
		s_RegisteredComponents[component].AddFunc(this, entity);
	}

	void* EntityRegistry::GetComponent(const EntityID& entity, const std::string& component)
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID(component);

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return (void*)(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		return nullptr;
	}

	std::vector<ComponentMeta> EntityRegistry::GetComponents(const EntityID& entity) const
	{
		if (!IsValidEntity(entity)) return std::vector<ComponentMeta>();

		std::vector<ComponentMeta> components;
		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			if (m_Entities[GetEntityIndex(entity)].Components.test(i))
				components.push_back(s_RegisteredComponents[m_ComponentPools[i]->GetType()]);
		}

		return components;
	}

	void EntityRegistry::Construct()
	{
		auto tag = ComponentFactory<Tag>()
			.Data<&Tag::Name>("Name", offsetof(Tag, Name))
			.Register();

		auto transform = ComponentFactory<Transform>()
			.Data<&Transform::Position>("Position", offsetof(Transform, Position))
			.Data<&Transform::Rotation>("Rotation", offsetof(Transform, Rotation))
			.Data<&Transform::Scale>("Scale", offsetof(Transform, Scale))
			.Register();

		auto spriteRenderer = ComponentFactory<SpriteRenderer>()
			.Data<&SpriteRenderer::Color>("Color", offsetof(SpriteRenderer, Color))
			.Register();
	}

	void EntityRegistry::RegisterComponent(const ComponentMeta& meta)
	{
		s_RegisteredComponents[meta.Object.Name] = meta;
	}

	size_t EntityRegistry::FindComponentID(const std::string& component) const
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