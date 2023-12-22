#include "rbpch.h"
#include "Scene.h"
#include "RBEngine/Rendering/Renderer.h"

namespace RB
{
	Ref<Scene> Scene::s_Active = nullptr;

	void Scene::OnRuntimeUpdate()
	{
	}

	void Scene::OnEditorUpdate(const Camera& camera, const Transform& cameraTransform)
	{
		Renderer::BeginFrame(camera, cameraTransform);
		for (auto ent : EntityRegistry::View<SpriteRenderer>(m_Registry))
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
}