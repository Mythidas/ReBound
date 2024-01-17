#pragma once

#include "rbpch.h"
#include "EntityEntry.h"
#include "ComponentPool.h"
#include "RBEngine/Reflection/Type.h"
#include "RBEngine/Reflection/Meta.h"

namespace RB
{
	class Entity;

	class SceneRegistry
	{
		friend class SceneSerializer;
	public:
		SceneRegistry();
		~SceneRegistry();

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);
		void DestroyEntity(const EntityID& entity);

		template <typename T>
		T* AddComponent(const EntityID& entity);
		template <typename T>
		T* GetComponent(const EntityID& entity) const;
		template <typename T>
		bool HasComponent(const EntityID& entity) const;
		template <typename T>
		void RemoveComponent(const EntityID& entity);

		void AddComponent(const EntityID& entity, const TypeID& component);
		void* GetComponent(const EntityID& entity, const TypeID& component) const;
		bool HasComponent(const EntityID& entity, const TypeID& component) const;
		void RemoveComponent(const EntityID& entity, const TypeID& component);

		std::vector<ComponentMeta> GetComponents(const EntityID& entity) const;

	public:
		template <typename ...Components>
		struct View
		{
			View(SceneRegistry& registry)
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
				Iterator(SceneRegistry& registry, size_t index, ComponentMask components, bool all)
					: _Registry(registry), Index(index), Mask(components), All(all)
				{
				}

				EntityEntry operator*() const
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

				SceneRegistry& _Registry;
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
			SceneRegistry& m_Registry;
		};

		template <typename ...Components>
		inline View<Components...> GetView() { return View<Components...>(*this); }

	private:
		template <typename T>
		size_t FindComponentID() const;
		size_t FindComponentID(const TypeID& component) const;

		bool IsValidEntity(EntityID entity) const;
		EntityID GetEntityID(EntityIndex index, EntityVersion version) const;
		EntityIndex GetEntityIndex(EntityID id) const;
		EntityVersion GetEntityVersion(EntityID id) const;

	private:
		EntityEntry* m_Entities;
		EntityIndex m_EntityIndex;
		std::vector<EntityID> m_FreeEntities;
		std::vector<ComponentPool*> m_ComponentPools;
	};

	template<typename T>
	inline T* SceneRegistry::AddComponent(const EntityID& entity)
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
	inline T* SceneRegistry::GetComponent(const EntityID& entity) const
	{
		if (!IsValidEntity(entity)) return nullptr;

		size_t compID = FindComponentID<T>();

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return static_cast<T*>(m_ComponentPools[compID]->GetData(GetEntityIndex(entity)));

		return nullptr;
	}

	template<typename T>
	inline bool SceneRegistry::HasComponent(const EntityID& entity) const
	{
		if (!IsValidEntity(entity)) return false;

		size_t compID = FindComponentID<T>();

		if (m_Entities[GetEntityIndex(entity)].Components.test(compID))
			return false;

		return false;
	}

	template<typename T>
	inline void SceneRegistry::RemoveComponent(const EntityID& entity)
	{
		if (!IsValidEntity(entity)) return;

		size_t compID = FindComponentID<T>();
		m_Entities[GetEntityIndex(entity)].Components.reset(compID);
	}

	template<typename T>
	inline size_t SceneRegistry::FindComponentID() const
	{
		return FindComponentID(Type<T>().Name());
	}
}