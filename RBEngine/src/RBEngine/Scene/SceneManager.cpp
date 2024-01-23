#include "rbpch.h"
#include "SceneManager.h"
#include "RBEngine/Core/Project.h"

namespace RB
{
	Ref<Scene> SceneManager::s_ActiveScene = CreateRef<Scene>();
	Ref<Scene> SceneManager::s_StoredScene = nullptr;

	void SceneManager::LoadScene(const File& path, bool cacheOld)
	{
		if (cacheOld)
			s_StoredScene = s_ActiveScene;

		Ref<Scene> scene = CreateRef<Scene>(path);
		scene->Load();

		if (_IsValidScene(scene))
			s_ActiveScene = scene;
	}

	void SceneManager::LoadScene(Ref<Scene> scene, bool cacheOld)
	{
		if (cacheOld)
			s_StoredScene = s_ActiveScene;

		if (_IsValidScene(scene))
			s_ActiveScene = scene;
	}

	void SceneManager::LoadCachedScene()
	{
		if (_IsValidScene(s_StoredScene))
			s_ActiveScene = s_StoredScene;
	}

	bool SceneManager::_IsValidScene(Ref<Scene> scene)
	{
		return scene && scene->IsValid();
	}
}