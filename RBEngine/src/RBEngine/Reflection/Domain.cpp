#include "rbpch.h"
#include "Domain.h"
#include "ObjectFactory.h"
#include "ComponentFactory.h"
#include "RBEngine/Math/Vector.h"
#include "RBEngine/Scene/Components.h"

namespace RB
{
	std::unordered_map<std::string, ObjectMeta> Domain::s_RegisteredObjects;
	std::unordered_map<std::string, ComponentMeta> Domain::s_RegisteredComponents;

	void Domain::Construct()
	{
		// Register Objects
		auto vec3 = ObjectFactory<Vector3>()
			.Data<&Vector3::x>("X", offsetof(Vector3, x))
			.Data<&Vector3::y>("Y", offsetof(Vector3, y))
			.Data<&Vector3::z>("Z", offsetof(Vector3, z))
			.Register();


		// Register Components
		auto tag = ComponentFactory<Tag>()
			.Data<&Tag::Name>("Name", offsetof(Tag, Name))
			.Data<&Tag::Active>("Active", offsetof(Tag, Active))
			.Register();

		auto transform = ComponentFactory<Transform>()
			.Data<&Transform::Position>("Position", offsetof(Transform, Position))
			.Data<&Transform::Rotation>("Rotation", offsetof(Transform, Rotation))
			.Data<&Transform::Scale>("Scale", offsetof(Transform, Scale))
			.Register();

		auto spriteRenderer = ComponentFactory<SpriteRenderer>()
			.Data<&SpriteRenderer::Color>("Color", offsetof(SpriteRenderer, Color))
			.Register();
	}

	void Domain::RegisterObject(const ObjectMeta& meta)
	{
		s_RegisteredObjects[meta.Info.ID] = meta;
	}

	const ObjectMeta& Domain::FindObject(const TypeID& id)
	{
		return s_RegisteredObjects[id];
	}

	const std::unordered_map<TypeID, ObjectMeta>& Domain::GetAllObjects()
	{
		return s_RegisteredObjects;
	}

	void Domain::RegisterComponent(const ComponentMeta& meta)
	{
		s_RegisteredComponents[meta.Info.ID] = meta;
	}

	const ComponentMeta& Domain::FindComponent(const TypeID& id)
	{
		return s_RegisteredComponents[id];
	}

	const std::unordered_map<TypeID, ComponentMeta>& Domain::GetAllComponents()
	{
		return s_RegisteredComponents;
	}
}