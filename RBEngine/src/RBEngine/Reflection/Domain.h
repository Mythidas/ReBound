#pragma once

#include "Meta.h"

#include <unordered_map>

namespace RB
{
	class Domain
	{
	public:
		static void Construct();

		static void RegisterObject(const ObjectMeta& meta);
		static ObjectMeta FindObject(const TypeID& id);

	private:
		static std::unordered_map<TypeID, ObjectMeta> s_RegisteredObjects;
	};
}