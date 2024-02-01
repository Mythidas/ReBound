#pragma once

#include "Meta.h"
#include "Domain.h"
#include "RBEngine/Scene/Scene.h"

#include <functional>

namespace RB
{
	template <typename T>
	class ComponentFactory
	{
	public:
		ComponentFactory(Domain* domain) : m_Domain(domain) {}

		template <auto Data>
		inline ComponentFactory<T>& Data(const std::string& id, size_t offset)
		{
			if constexpr (std::is_member_object_pointer_v<decltype(Data)>)
			{
				using data_type = std::remove_reference_t<std::invoke_result_t<decltype(Data), T&>>;
				Type<data_type> type;
				if (type.Ref() != TypeRef::Unknown)
				{
					m_Vars.push_back({ id, type.Name(), type.Ref(), offset});
				}
			}

			return *this;
		}

		inline ComponentMeta Register()
		{
			ComponentMeta meta;
			meta.Info.DebugName = Type<T>().Name();
			meta.Info.ID = Type<T>().ID();
			meta.Vars = m_Vars;
			meta.AddFunc = _AddComponent;
			m_Domain->RegisterComponent(meta);
			return meta;
		}

	public:
		static inline T* _AddComponent(SceneRegistry* registry, EntityID entity)
		{
			return registry->AddComponent<T>(entity);
		}

	private:
		Domain* m_Domain;
		std::vector<VariableMeta> m_Vars;
	};
}