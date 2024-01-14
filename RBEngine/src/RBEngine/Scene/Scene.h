#pragma once

#include "Transform.h"
#include "SceneRegistry.h"
#include "RBEngine/Rendering/Camera.h"
#include "RBEngine/Utils/FileSystem.h"

namespace RB
{
	class Scene
	{
		friend class SceneSerializer;

	public:
		Scene() = default;
		Scene(const FileSystem& path);

		void OnRuntimeUpdate();
		void OnEditorUpdate(const Camera& camera, const Transform& cameraTransform);

		SceneRegistry& GetRegistry() { return m_Registry; }

	public:
		static Ref<Scene> Create();
		static Ref<Scene> Create(const FileSystem& path);
		static Ref<Scene>& GetActive() { return s_Active; }
		
	private:
		static Ref<Scene> s_Active;

		SceneRegistry m_Registry;
		FileSystem m_LocalPath;
	};
}