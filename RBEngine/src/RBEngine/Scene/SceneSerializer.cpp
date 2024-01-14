#include "rbpch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "RBEngine/Reflection/Domain.h"

#include <yaml-cpp/yaml.h>

namespace RB
{
	namespace Utils
	{
		void SerializeVariable(YAML::Emitter& out, char* data, const VariableMeta& meta)
		{
			out << YAML::Key << meta.Info.DebugName;

			switch (meta.Ref)
			{
			case TypeRef::Object:
			{
				ObjectMeta obj = Domain::FindObject(meta.Info.ID);
				for (auto& var : obj.Vars)
				{
					out << YAML::Value << YAML::BeginMap;
					SerializeVariable(out, data + var.Offset, var);
					out << YAML::EndMap;
				}

				break;
			}
			case TypeRef::Component:
			{
				break;
			}
			case TypeRef::Int32: out << YAML::Value << *(int*)(data + meta.Offset); break;
			case TypeRef::Int64: out << YAML::Value << *(int64_t*)(data + meta.Offset); break;
			case TypeRef::UInt32: out << YAML::Value << *(uint32_t*)(data + meta.Offset); break;
			case TypeRef::UInt64: out << YAML::Value << *(uint64_t*)(data + meta.Offset); break;
			case TypeRef::Float: out << YAML::Value << *(float*)(data + meta.Offset); break;
			case TypeRef::Double: out << YAML::Value << *(double*)(data + meta.Offset); break;
			case TypeRef::String: out << YAML::Value << *(std::string*)(data + meta.Offset); break;
			}
		}

		void SerializeEntity(YAML::Emitter& out, const Entity& entity)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Entity" << YAML::Value << int64_t(0);
			out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;

			for (auto& comp : entity.GetComponents())
			{
				char* data = (char*)entity.GetComponent(comp.Info.ID);

				out << YAML::Key << comp.Info.DebugName << YAML::Value << YAML::BeginMap;
				for (auto& var : comp.Vars)
				{
					SerializeVariable(out, data, var);
				}
				out << YAML::EndMap;
			}

			out << YAML::EndMap;
			out << YAML::EndMap;
		}
	}

	SceneSerializer::SceneSerializer(Ref<Scene> scene)
		: m_Scene(scene)
	{
	}

	void SceneSerializer::Serialize()
	{
		if (!_IsValidScene()) return;

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Scene name here";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (Entity ent : m_Scene->m_Registry.GetView())
		{
			Utils::SerializeEntity(out, ent);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		m_Scene->m_LocalPath.Write(out.c_str());
	}

	void SceneSerializer::Deserialize()
	{
		if (!_IsValidScene()) return;

		YAML::Node in = YAML::Load(m_Scene->m_LocalPath.StreamString());
	}

	Ref<Scene> SceneSerializer::Duplicate()
	{
		return Ref<Scene>();
	}

	bool SceneSerializer::_IsValidScene()
	{
		if (m_Scene->m_LocalPath.ToString().empty())
		{
			Debug::Log::Error("Failed to load scene! No local path was set!");
			return false;
		}

		return true;
	}
}