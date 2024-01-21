#include "rbpch.h"
#include "SceneManager.h"

namespace RB
{
	std::unordered_map<std::string, File> SceneManager::s_Scenes;
	Ref<Scene> SceneManager::s_ActiveScene;

	void SceneManager::LoadScene(const std::string& name)
	{
		Ref<Scene> scene = Scene::Create(s_Scenes[name]);
		scene->Load();
		s_ActiveScene = scene;
	}

	void SceneManager::SetActive(Ref<Scene> scene)
	{
		if (scene->IsValid())
			s_ActiveScene = scene;
	}

	void SceneManager::_Construct()
	{

	}
}