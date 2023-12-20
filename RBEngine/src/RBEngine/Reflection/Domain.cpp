#include "rbpch.h"
#include "Domain.h"

namespace RB
{
	std::unordered_map<std::string, ObjectMeta> Domain::s_RegisteredObjects;

	void Domain::RegisterObject(const ObjectMeta& meta)
	{
		s_RegisteredObjects[meta.Name] = meta;
	}

	ObjectMeta Domain::FindObject(const std::string& id)
	{
		return s_RegisteredObjects[id];
	}
}