#pragma once

#include "rbpch.h"
#include "Meta.h"

namespace RB
{
	class Domain
	{
	public:
		static void RegisterObject(const ObjectMeta& meta);
		static ObjectMeta FindObject(const std::string& id);

	private:
		static std::unordered_map<std::string, ObjectMeta> s_RegisteredObjects;
	};
}