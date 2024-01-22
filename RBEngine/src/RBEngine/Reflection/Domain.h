#pragma once

#include "Meta.h"

#include <unordered_map>

namespace RB
{
	class Domain
	{
	public:
		static void RegisterObject(const ObjectMeta& meta);
		static const ObjectMeta& FindObject(const TypeID& id);
		static const std::unordered_map<TypeID, ObjectMeta>& GetAllObjects();

		static void RegisterComponent(const ComponentMeta& meta);
		static const ComponentMeta& FindComponent(const TypeID& id);
		static const std::unordered_map<TypeID, ComponentMeta>& GetAllComponents();

	private:
		friend class Application;

	private:
		static void _Construct();

	private:
		static std::unordered_map<TypeID, ObjectMeta> s_RegisteredObjects;
		static std::unordered_map<TypeID, ComponentMeta> s_RegisteredComponents;
	};
}