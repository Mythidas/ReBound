#pragma once

#include "Transform.h"
#include "SceneRegistry.h"
#include "RBEngine/Rendering/Camera.h"
#include "RBEngine/Utils/File.h"

namespace RB
{
	class Scene
	{
		friend class SceneSerializer;
	public:
		Scene() = default;
		Scene(const File& path);

		void OnRuntimeUpdate();
		void OnEditorUpdate(const Camera& camera, const Transform& cameraTransform);

		inline SceneRegistry& GetRegistry() { return m_Registry; }
		inline const File& GetPath() const { return m_LocalPath; }

	public:
		static Ref<Scene> Create();
		static Ref<Scene> Create(const File& path);
		
		inline static void SetActive(Ref<Scene> active) { s_Active = active; }
		inline static Ref<Scene>& GetActive() { return s_Active; }
		
	private:
		static Ref<Scene> s_Active;

		SceneRegistry m_Registry;
		File m_LocalPath;
	};
}