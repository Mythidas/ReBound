#pragma once

#include "rbpch.h"
#include "Meta.h"
#include "Type.h"
#include "Domain.h"

namespace RB
{
	template <typename T>
	class ObjectFactory
	{
	public:
		ObjectFactory(Domain* domain) : m_Domain(domain) {}

		template <auto Data>
		inline ObjectFactory<T>& Data(const std::string& id, size_t offset)
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

		inline ObjectMeta Register()
		{
			ObjectMeta meta;
			meta.Info.DebugName = Type<T>().Name();
			meta.Info.ID = Type<T>().ID();
			meta.Vars = m_Vars;
			m_Domain->RegisterObject(meta);
			return meta;
		}

	private:
		Domain* m_Domain;
		std::vector<VariableMeta> m_Vars;
	};
}