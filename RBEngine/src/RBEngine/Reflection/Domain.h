#pragma once

#include "Meta.h"
#include "RBEngine/Utils/Singleton.h"

#include <unordered_map>

namespace RB
{
	class Domain : public Singleton<Domain>
	{
	public:
		Domain();

	public:
		void RegisterObject(const ObjectMeta& meta);
		const ObjectMeta& FindObject(const TypeID& id);
		const std::unordered_map<TypeID, ObjectMeta>& GetAllObjects();

		void RegisterComponent(const ComponentMeta& meta);
		const ComponentMeta& FindComponent(const TypeID& id);
		const std::unordered_map<TypeID, ComponentMeta>& GetAllComponents();

	private:
		friend class Application;

	private:
		std::unordered_map<TypeID, ObjectMeta> m_RegisteredObjects;
		std::unordered_map<TypeID, ComponentMeta> m_RegisteredComponents;
	};
}