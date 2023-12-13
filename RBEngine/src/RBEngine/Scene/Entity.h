#pragma once

#include "RBEngine/Utils/UUID.h"

#include <bitset>

namespace RB
{
	static const size_t MAX_ENTITIES = 1000;
	static const size_t MAX_COMPONENTS = 32;

	using EntityID = uint64_t;
	using EntityIndex = uint32_t;
	using EntityVersion = uint32_t;
	using ComponentMask = std::bitset<MAX_COMPONENTS>;

	struct Entity
	{
		EntityID ID;
		ComponentMask Components;

		Entity() : ID(0) {}

		operator EntityID() const
		{
			return ID;
		}
	};
}