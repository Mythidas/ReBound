#pragma once

#include "Scene.h"
#include "RBEngine/Debug/Result.h"

namespace YAML
{
	class Emitter;
	class Node;
}

namespace RB
{
	class SceneSerializer
	{
	public:
		SceneSerializer(Ref<Scene> scene);

		Debug::Result Serialize();
		Debug::Result Deserialize();
		Ref<Scene> Copy();

	private:
		bool _IsValidScene();
		void _GetOutData(YAML::Emitter& out);
		void _SerializeEntity(YAML::Emitter& out, const Entity& entity);
		void _SerializeVariable(YAML::Emitter& out, char* data, const VariableMeta& meta);
		void _DeserializeEntity(YAML::Node& in, Ref<Scene> scene, std::unordered_map<EntityID, EntityID>& idRemap);
		void _DeserializeVariable(YAML::Node& in, Ref<Scene> scene, const VariableMeta& meta, char* data);

	private:
		Ref<Scene> m_Scene;
	};
}