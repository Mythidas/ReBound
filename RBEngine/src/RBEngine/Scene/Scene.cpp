#include "rbpch.h"
#include "Scene.h"
#include "RBEngine/Rendering/Renderer.h"

namespace RB
{
	Ref<Scene> Scene::s_Active = nullptr;

	Scene::Scene(const File& path)
		: m_LocalPath(path)
	{
	}

	void Scene::OnRuntimeUpdate()
	{
	}

	void Scene::OnEditorUpdate(const Camera& camera, const Transform& cameraTransform)
	{
		Renderer::BeginFrame(camera, cameraTransform);
		for (const auto& ent : SceneRegistry::View<SpriteRenderer>(m_Registry))
		{
			auto transform = m_Registry.GetComponent<Transform>(ent);
			auto sprite = m_Registry.GetComponent<SpriteRenderer>(ent);
			Renderer::DrawQuad(*transform, *sprite);
		}
		Renderer::EndFrame();
	}

	Ref<Scene> Scene::Create()
	{
		Ref<Scene> scene = CreateRef<Scene>();
		if (!s_Active) s_Active = scene;
		return scene;
	}

	Ref<Scene> Scene::Create(const File& path)
	{
		Ref<Scene> scene = CreateRef<Scene>(path);
		if (!s_Active) s_Active = scene;
		return scene;
	}
}