#include "rbpch.h"
#include "Domain.h"
#include "ObjectFactory.h"
#include "RBEngine/Math/Vector.h"

namespace RB
{
	std::unordered_map<std::string, ObjectMeta> Domain::s_RegisteredObjects;

	void Domain::Construct()
	{
		auto vec3 = ObjectFactory<Vector3>()
			.Data<&Vector3::x>("X", offsetof(Vector3, x))
			.Data<&Vector3::y>("Y", offsetof(Vector3, y))
			.Data<&Vector3::z>("Z", offsetof(Vector3, z))
			.Register();
	}

	void Domain::RegisterObject(const ObjectMeta& meta)
	{
		s_RegisteredObjects[meta.Name] = meta;
	}

	ObjectMeta Domain::FindObject(const std::string& id)
	{
		return s_RegisteredObjects[id];
	}
}