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
		T* AddComponent()
		{
			if (!m_Registry) return nullptr;
			return m_Registry->AddComponent<T>(m_ID);
		}
		template <typename T>
		T* GetComponent() const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->GetComponent<T>(m_ID);
		}
		template <typename T>
		T* HasComponent() const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->HasComponent<T>(m_ID);
		}
		template <typename T>
		void RemoveComponent()
		{
			if (!m_Registry) return;
			m_Registry->RemoveComponent<T>(m_ID);
		}

		std::vector<ComponentMeta> GetComponents() const
		{
			if (!m_Registry) return std::vector<ComponentMeta>();
			return m_Registry->GetComponents(m_ID);
		}

		void AddComponent(const TypeID& component)
		{
			if (!m_Registry) return;
			return m_Registry->AddComponent(m_ID, component);
		}
		void* GetComponent(const TypeID& component) const
		{
			if (!m_Registry) return nullptr;
			return m_Registry->GetComponent(m_ID, component);
		}
		bool HasComponent(const TypeID& component) const
		{
			if (!m_Registry) return false;
			return m_Registry->HasComponent(m_ID, component);
		}
		void RemoveComponent(const TypeID& component)
		{
			if (!m_Registry) return;
			return m_Registry->RemoveComponent(m_ID, component);
		}

		void Destroy()
		{
			if (!m_Registry) return;
			m_Registry->DestroyEntity(m_ID);
		}

		bool IsActive() const;

		EntityID GetID() const
		{
			return m_ID;
		}

	public:
		static Entity Create();
		static Entity Create(const std::string& name);

	public:
		operator UUID() const
		{
			return UUID(m_ID);
		}

		operator EntityID() const
		{
			return m_ID;
		}

	private:
		EntityID m_ID;
		SceneRegistry* m_Registry;
	};
}