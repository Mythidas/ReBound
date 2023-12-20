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
			meta.Name = Type<T>().Name();
			meta.Vars = m_Vars;
			Domain::RegisterObject(meta);
			return meta;
		}

	private:
		std::vector<VariableMeta> m_Vars;
	};
}