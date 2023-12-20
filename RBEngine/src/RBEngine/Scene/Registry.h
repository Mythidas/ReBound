#pragma once

#include "rbpch.h"
#include "EntityEntry.h"
#include "ComponentPool.h"
#include "RBEngine/Reflection/Meta.h"
#include "RBEngine/Reflection/Type.h"

namespace RB
{
	class Registry;

	struct ComponentMeta
	{
		ObjectMeta Object;
		std::function<void(Registry*, EntityID)> AddFunc;
	};

	class Registry
	{
	public:
		Registry();
		~Registry();

		EntityID CreateEntity();
		void DestroyEntity(const EntityID& entity);

		void AddComponent(const std::string& component, const EntityID& entity);
		template <typename T>
		T* AddComponent(const EntityID& entity);
		template <typename T>
		T* GetComponent(const EntityID& entity);
		template <typename T>
		void RemoveComponent(const EntityID& entity);

	public:
		static void RegisterComponent(const ComponentMeta& meta);

	public:
		template <typename ...Components>
		struct View
		{
			View(Registry& registry)
				: m_Registry(registry)
			{
				if (sizeof...(Components) == 0)
				{
					m_All = true;
				}
				else
				{
					size_t componentIDs[] = { 0, m_Registry.FindComponentID<Components>()... };
					for (size_t i = 1; i < (sizeof...(Components) + 1); i++)
					{
						if (componentIDs[i] != UINT64_MAX)
							m_Mask.set(componentIDs[i]);
						else
						{
							m_Invalid = true;
							break;
						}
					}
				}
			}

			struct Iterator
			{
				Iterator(Registry& registry, size_t index, ComponentMask components, bool all)
					: _Registry(registry), Index(index), Mask(components), All(all)
				{
				}

				EntityID operator*() const
				{
					return _Registry.m_Entities[Index];
				}

				bool operator ==(const Iterator& other) const
				{
					return Index == other.Index;
				}

				bool operator !=(const Iterator& other) const
				{
					return Index != other.Index;
				}

				Iterator& operator++()
				{
					do
					{
						Index++;
					} while (Index < _Registry.m_EntityIndex && !IsValidIndex());
					return *this;
				}

				bool IsValidIndex()
				{
					return _Registry.IsValidEntity(_Registry.m_Entities[Index]) && (All || Mask == (Mask & _Registry.m_Entities[Index].Components));
				}

				Registry& _Registry;
				size_t Index{ 0 };
				ComponentMask Mask;
				bool All{ false };
			};

			const Iterator begin() const
			{
				size_t first = m_Invalid ? m_Registry.m_EntityIndex : 0;
				while (first < m_Registry.m_EntityIndex &&
					(m_Mask != (m_Mask & m_Registry.m_Entities[first].Components) ||
						!m_Registry.IsValidEntity(m_Registry.m_Entities[first].ID)))
				{
					first++;
				}

				return Iterator(m_Registry, first, m_Mask, m_All);
			}

			const Iterator end() const
			{
				return Iterator(m_Registry, m_Registry.m_EntityIndex, m_Mask, m_All);
			}

		private:
			bool m_All{ false };
			bool m_Invalid{ false };
			ComponentMask m_Mask;
			Registry& m_Registry;
		};

	private:
		template <typename T>
		size_t FindComponentID();

		bool IsValidEntity(EntityID entity);
		EntityID GetEntityID(EntityIndex index, EntityVersion version);
		EntityIndex GetEntityIndex(EntityID id);
		EntityVersion GetEntityVersion(EntityID id);

	private:
		static std::unordered_map<std::string, ComponentMeta> s_RegisteredComponents;

	private:
		EntityEntry* m_Entities;
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
			m_ComponentPools.push_back(new ComponentPool(Type<T>().Name(), sizeof(T)));
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
			if (m_ComponentPools[i]->IsType(componentType.Name()))
				return i;
		}

		return m_ComponentPools.size();
	}
}