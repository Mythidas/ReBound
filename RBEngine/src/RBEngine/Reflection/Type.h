#pragma once

#include <type_traits>
#include <string>

namespace RB
{
	using TypeID = std::string;

	// Used as a tag to know which types are objects at compile time
	// Objects still need to have a registered ObjectMeta with the Domain to be dereferenced
	class Object {};

	// Used as a tag to know which types are objects at compile time
	// Objects still need to have a registered ComponentMeta with the ComponentRegistry to be dereferenced
	class Component {};

	enum class TypeRef : int
	{
		Unknown = 0,
		Object,
		Component,
		String,
		Int32,
		Int64,
		UInt32,
		UInt64,
		Float,
		Double
	};

	template<typename T>
	class Type
	{
	public:
		std::string Name() const
		{
			return typeid(T).name();
		}

		TypeID ID() const
		{
			return typeid(T).name();
		}

		TypeRef Ref() const
		{
			if constexpr (std::is_convertible_v<T, Object>)
				return TypeRef::Object;
			else if constexpr (std::is_convertible_v<T, Component>)
				return TypeRef::Component;
			else if constexpr (std::is_same_v<T, std::string>)
				return TypeRef::String;
			else if constexpr (std::is_same_v<T, int>)
				return TypeRef::Int32;
			else if constexpr (std::is_same_v<T, long long>)
				return TypeRef::Int64;
			else if constexpr (std::is_same_v<T, unsigned int>)
				return TypeRef::UInt32;
			else if constexpr (std::is_same_v<T, unsigned long long>)
				return TypeRef::UInt64;
			else if constexpr (std::is_same_v<T, float>)
				return TypeRef::Float;
			else if constexpr (std::is_same_v<T, double>)
				return TypeRef::Double;

			return TypeRef::Unknown;
		}
	};
}