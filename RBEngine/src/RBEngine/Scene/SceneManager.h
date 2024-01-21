#pragma once

#include "Scene.h"
#include "RBEngine/Utils/File.h"
#include "RBEngine/Core/UUID.h"

#include <unordered_map>

namespace RB
{
	class SceneManager
	{
	public:
		static void LoadScene(const std::string& name);

		static Ref<Scene> GetActive() { return s_ActiveScene; }
		
		static void SetActive(Ref<Scene> scene);

	private:
		friend class Application;
		static void _Construct();

	private:
		static std::unordered_map<std::string, File> s_Scenes;
		static Ref<Scene> s_ActiveScene;
	};
}