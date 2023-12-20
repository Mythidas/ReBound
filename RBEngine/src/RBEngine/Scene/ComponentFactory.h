#pragma once

#include "rbpch.h"
#include "RBEngine/Scene/Registry.h"
#include "RBEngine/Reflection/Meta.h"

namespace RB
{
	template <typename T>
	class ComponentFactory
	{
	public:
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
			ObjectMeta object;
			object.Name = Type<T>().Name();
			object.Vars = m_Vars;

			ComponentMeta meta;
			meta.Object = object;
			meta.AddFunc = _AddComponent;

			Registry::RegisterComponent(meta);
			return meta;
		}

	public:
		static inline T* _AddComponent(Registry* registry, EntityID entity)
		{
			return registry->AddComponent<T>(entity);
		}

	private:
		std::vector<VariableMeta> m_Vars;
	};
}