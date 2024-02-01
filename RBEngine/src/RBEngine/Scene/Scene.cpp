#include "rbpch.h"
#include "Scene.h"
#include "Entity.h"
#include "SceneSerializer.h"
#include "RBEngine/Components/Tag.h"
#include "RBEngine/Rendering/Renderer.h"

namespace RB
{
	Scene::Scene(const File& path)
		: m_LocalPath(path)
	{
		if (!path.Exists())
			m_DataState = SceneDataState::DeSynced;
	}

	bool Scene::Save()
	{
		if (m_DataState == SceneDataState::Synced) return true;

		SceneSerializer serial(shared_from_this());
		if (Debug::Result result = serial.Serialize(); result & Debug::ResultCode::Success)
		{
			Debug::Log::Info("Saved Scene!");
			m_DataState = SceneDataState::Synced;
			return true;
		}
		else
		{
			Debug::Log::Error(result.Message);
			return false;
		}
	}

	bool Scene::Load()
	{
		SceneSerializer serial(shared_from_this());
		if (Debug::Result result = serial.Deserialize(); result & Debug::ResultCode::Success)
		{
			m_DataState = SceneDataState::Synced;
			Debug::Log::Info("Loaded Scene!");
			return true;
		}
		else
		{
			Debug::Log::Error(result.Message);
			return false;
		}
	}

	Ref<Scene> Scene::Copy()
	{
		SceneSerializer serial(shared_from_this());
		return serial.Copy();
	}

	void Scene::OnUpdate(Camera* camera, Transform* transform)
	{
		if (m_State == SceneState::Editing)
		{
			if (!camera || !transform) return;

			Renderer::BeginFrame(*camera, *transform);
			for (Entity ent : m_Registry.GetView<SpriteRenderer>())
			{
				if (ent.IsActive()) continue;

				auto transform = m_Registry.GetComponent<Transform>(ent);
				auto sprite = m_Registry.GetComponent<SpriteRenderer>(ent);
				Renderer::DrawQuad(transform->Position, transform->Rotation, transform->Scale, sprite->Color);
			}
			Renderer::EndFrame();
		}
	}

	bool Scene::IsValid() const
	{
		return m_LocalPath.Exists();
	}
}