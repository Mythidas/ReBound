#pragma once

#include "EntityEntry.h"
#include "SceneRegistry.h"

namespace RB
{
	// Helper class for short handing a lot of registry functions
	class Entity
	{
	public:
		Entity(const EntityID& id);
		Entity(const EntityEntry& entry);
		Entity(const EntityID& id, SceneRegistry& registry);

		template <typename T>
		inline T* AddComponent()
		{
			if (!m_Registry) return nullptr;
			return m_Registry->AddComponent<T>(m_ID);
		}
		template <typename T>
		inline T* GetComponent() const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->GetComponent<T>(m_ID);
		}
		template <typename T>
		inline T* HasComponent() const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->HasComponent<T>(m_ID);
		}
		template <typename T>
		inline void RemoveComponent()
		{
			if (!m_Registry) return;
			m_Registry->RemoveComponent<T>(m_ID);
		}

		inline std::vector<ComponentMeta> GetComponents() const
		{
			if (!m_Registry) return std::vector<ComponentMeta>();
			return m_Registry->GetComponents(m_ID);
		}

		inline void AddComponent(const TypeID& component)
		{
			if (!m_Registry) return;
			return m_Registry->AddComponent(m_ID, component);
		}
		inline void* GetComponent(const TypeID& component) const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->GetComponent(m_ID, component);
		}
		inline bool HasComponent(const TypeID& component) const
		{
			if (!m_Registry) return false;
			return m_Registry->HasComponent(m_ID, component);
		}
		inline void RemoveComponent(const TypeID& component)
		{
			if (!m_Registry) return;
			return m_Registry->RemoveComponent(m_ID, component);
		}

		inline void Destroy()
		{
			if (!m_Registry) return;
			m_Registry->DestroyEntity(m_ID);
		}

		inline EntityID GetID() const
		{
			return m_ID;
		}

		operator UUID() const
		{
			return UUID(m_ID);
		}

		operator EntityID() const
		{
			return m_ID;
		}

	public:
		static Entity CreateDir();
		static Entity CreateDir(const std::string& name);

	private:
		EntityID m_ID;
		SceneRegistry* m_Registry;
	};
}