#include "rbpch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "RBEngine/Reflection/Domain.h"

#include <yaml-cpp/yaml.h>

namespace RB
{
	SceneSerializer::SceneSerializer(Ref<Scene> scene)
		: m_Scene(scene)
	{
	}

	Debug::Result SceneSerializer::Serialize()
	{
		if (!_IsValidScene()) return { Debug::ResultCode::Invalid, "Invalid Scene!" };

		YAML::Emitter out;
		_GetOutData(out);

		m_Scene->GetPath().Write(out.c_str());

		return Debug::ResultCode::Success;
	}

	Debug::Result SceneSerializer::Deserialize()
	{
		if (!_IsValidScene()) return { Debug::ResultCode::Invalid, "Invalid Scene!" };

		YAML::Node in = YAML::Load(m_Scene->m_LocalPath.ReadString());
		if (!in["Scene"]) return { Debug::ResultCode::Invalid, "Scene file is invalid format!" };

		// TODO Myth: This does nothing right now???
		std::string sceneName = in["Scene"].as<std::string>();

		auto entities = in["Entities"];
		if (!entities) return { Debug::ResultCode::Invalid, "Scene file is invalid format!" };

		std::unordered_map<EntityID, EntityID> idRemap;
		for (auto ent : entities)
		{
			YAML::Node entIn = (YAML::Node)ent;
			_DeserializeEntity(entIn, m_Scene, idRemap);
		}

		return Debug::ResultCode::Success;
	}

	Ref<Scene> SceneSerializer::Copy()
	{
		if (!_IsValidScene()) return Ref<Scene>();

		YAML::Emitter out;
		_GetOutData(out);

		Ref<Scene> copy = CreateRef<Scene>();
		YAML::Node in = YAML::Load(out.c_str());

		auto entities = in["Entities"];
		std::unordered_map<EntityID, EntityID> idRemap;
		for (auto ent : entities)
		{
			YAML::Node entIn = (YAML::Node)ent;
			_DeserializeEntity(entIn, copy, idRemap);
		}

		return copy;
	}

	bool SceneSerializer::_IsValidScene()
	{
		if (!m_Scene || m_Scene->m_LocalPath.ToString().empty())
		{
			return false;
		}

		return true;
	}

	void SceneSerializer::_GetOutData(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Scene name here";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (Entity ent : m_Scene->m_Registry.GetView())
		{
			_SerializeEntity(out, ent);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;
	}

	void SceneSerializer::_SerializeEntity(YAML::Emitter& out, const Entity& entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << int64_t(0);
		out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;

		for (auto& comp : entity.GetComponents())
		{
			char* data = (char*)entity.GetComponent(comp.Info.ID);

			out << YAML::Key << comp.Info.ID << YAML::Value << YAML::BeginMap;
			for (auto& var : comp.Vars)
			{
				_SerializeVariable(out, data, var);
			}
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
		out << YAML::EndMap;
	}

	void SceneSerializer::_SerializeVariable(YAML::Emitter& out, char* data, const VariableMeta& meta)
	{
		out << YAML::Key << meta.Info.DebugName;

		switch (meta.Ref)
		{
		case TypeRef::Object:
		{
			ObjectMeta obj = Domain::Get().FindObject(meta.Info.ID);
			out << YAML::Value << YAML::BeginMap;
			for (auto& var : obj.Vars)
			{
				_SerializeVariable(out, data + meta.Offset, var);
			}
			out << YAML::EndMap;

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

	void SceneSerializer::_DeserializeEntity(YAML::Node& in, Ref<Scene> scene, std::unordered_map<EntityID, EntityID>& idRemap)
	{
		EntityID entID = in["Entity"].as<uint64_t>();
		Entity ent = m_Scene->GetRegistry().CreateEntity();
		idRemap[entID] = ent;

		auto comps = in["Components"];
		if (!comps) return;

		for (auto comp : comps)
		{
			ComponentMeta meta = Domain::Get().FindComponent(comp.first.as<std::string>());
			meta.AddFunc(&m_Scene->GetRegistry(), ent);
			char* data = (char*)ent.GetComponent(meta.Info.ID);
			if (!data) continue;
			
			YAML::Node compIn = comp.second;
			for (auto& var : meta.Vars)
			{
				if (compIn[var.Info.DebugName])
				{
					auto varIn = compIn[var.Info.DebugName];
					_DeserializeVariable(varIn, scene, var, data);
				}
			}
		}
	}

	void SceneSerializer::_DeserializeVariable(YAML::Node& in, Ref<Scene> scene, const VariableMeta& meta, char* data)
	{
		char* varData = data + meta.Offset;

		switch (meta.Ref)
		{
		case TypeRef::Object:
		{
			ObjectMeta obj = Domain::Get().FindObject(meta.Info.ID);
			for (auto& var : obj.Vars)
			{
				if (in[var.Info.DebugName])
				{
					auto varIn = in[var.Info.DebugName];
					_DeserializeVariable(varIn, scene, var, varData);
				}
			}

			break;
		}
		case TypeRef::Component:
		{
			break;
		}
		case TypeRef::Int32: *(int*)varData = in.as<int>(); break;
		case TypeRef::Int64: *(int64_t*)varData = in.as<int64_t>(); break;
		case TypeRef::UInt32: *(uint32_t*)varData = in.as<uint32_t>(); break;
		case TypeRef::UInt64: *(uint64_t*)varData = in.as<uint64_t>(); break;
		case TypeRef::Float: *(float*)varData = in.as<float>(); break;
		case TypeRef::Double: *(double*)varData = in.as<double>(); break;
		case TypeRef::String: *(std::string*)varData = in.as<std::string>(); break;
		}
	}
}