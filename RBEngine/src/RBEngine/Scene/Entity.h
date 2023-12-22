#pragma once

#include "EntityEntry.h"
#include "EntityRegistry.h"

namespace RB
{
	// Helper class for short handing a lot of registry functions
	class Entity
	{
	public:
		Entity(const EntityID& id);
		Entity(const EntityEntry& entry);
		Entity(const EntityID& id, EntityRegistry& registry);

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
		inline void RemoveComponent()
		{
			if (!m_Registry) return;
			m_Registry->RemoveComponent<T>(m_ID);
		}

		inline void Destroy()
		{
			if (!m_Registry) return;
			m_Registry->DestroyEntity(m_ID);
		}

		static Entity Create();
		static Entity Create(const std::string& name);

		operator EntityID() const
		{
			return m_ID;
		}

	private:
		EntityID m_ID;
		EntityRegistry* m_Registry;
	};
}