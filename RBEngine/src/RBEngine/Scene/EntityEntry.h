#pragma once

#include "RBEngine/Utils/UUID.h"

#include <bitset>

namespace RB
{
	inline static const size_t MAX_ENTITIES = 1000;
	inline static const size_t MAX_COMPONENTS = 32;

	using EntityID = uint64_t;
	using EntityIndex = uint32_t;
	using EntityVersion = uint32_t;
	using ComponentMask = std::bitset<MAX_COMPONENTS>;

	class EntityRegistry;

	struct EntityEntry
	{
		EntityID ID{ 0 };
		ComponentMask Components;
		EntityRegistry* Registry{ nullptr };

		EntityEntry() : ID(0) {}
		EntityEntry(EntityRegistry* registry) : ID(0), Registry(registry) {}

		operator EntityID() const
		{
			return ID;
		}
	};
}