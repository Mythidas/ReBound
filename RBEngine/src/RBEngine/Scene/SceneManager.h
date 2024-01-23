#pragma once

#include "Scene.h"
#include "RBEngine/Utils/File.h"
#include "RBEngine/Utils/Directory.h"
#include "RBEngine/Core/UUID.h"

#include <unordered_map>

namespace RB
{
	class SceneManager
	{
	public:
		static void LoadScene(const File& path, bool cacheOld = false);
		static void LoadScene(Ref<Scene> scene, bool cacheOld = false);
		static void LoadCachedScene();

		static Ref<Scene> GetActive() { return s_ActiveScene; }
		
	private:
		static bool _IsValidScene(Ref<Scene> scene);

	private:
		static Ref<Scene> s_ActiveScene;
		static Ref<Scene> s_StoredScene;
	};
}