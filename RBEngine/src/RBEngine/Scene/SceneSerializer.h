#pragma once

#include "Scene.h"

namespace RB
{
	class SceneSerializer
	{
	public:
		SceneSerializer(Ref<Scene> scene);

		void Serialize();
		void Deserialize();
		Ref<Scene> Duplicate();

	private:
		bool _IsValidScene();

	private:
		Ref<Scene> m_Scene;
	};
}