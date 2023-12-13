#pragma once

#include "Entity.h"
#include "ComponentPool.h"
#include "RBEngine/Utils/Type.h"

namespace RB
{
	class Registry
	{
	public:
		Registry();
		~Registry();

		EntityID CreateEntity();
		void DestroyEntity(const EntityID& entity);

		template <typename T>
		T* AddComponent(const EntityID& entity);
		template <typename T>
		T* GetComponent(const EntityID& entity);
		template <typename T>
		void RemoveComponent(const EntityID& entity);

	private:
		template <typename T>
		size_t FindComponentID();

		bool IsValidEntity(EntityID entity);
		EntityID GetEntityID(EntityIndex index, EntityVersion version);
		EntityIndex GetEntityIndex(EntityID id);
		EntityVersion GetEntityVersion(EntityID id);

	private:
		Entity* m_Entities;
		size_t m_EntityIndex;
		std::vector<EntityID> m_FreeEntities;
		std::vector<ComponentPool*> m_ComponentPools;
	};

	template<typename T>
	inline T* Registry::AddComponent(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID<T>();
		if (compID > MAX_COMPONENTS) return nullptr;

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return static_cast<T*>(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		if (compID >= m_ComponentPools.size())
		{
			m_ComponentPools.push_back(new ComponentPool(Type<T>().ToString(), sizeof(T)));
		}

		T* component = new (m_ComponentPools[compID]->GetData(GetEntityIndex(entity))) T();
		m_Entities[GetEntityIndex(entity)].Components.set(compID);
		return component;
	}

	template<typename T>
	inline T* Registry::GetComponent(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID<T>();

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return static_cast<T*>(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		return nullptr;
	}

	template<typename T>
	inline void Registry::RemoveComponent(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return;

		size_t compID = FindComponentID<T>();
		m_Entities[GetEntityIndex(entity)].Components.reset(compID);
	}

	template<typename T>
	inline size_t Registry::FindComponentID()
	{
		Type<T> componentType;

		for (size_t i = 0; i < m_ComponentPools.size(); i++)
		{
			if (m_ComponentPools[i]->IsType(componentType.ToString()))
				return i;
		}

		return m_ComponentPools.size();
	}
}