#pragma once

#include "Transform.h"
#include "SceneRegistry.h"
#include "RBEngine/Rendering/Camera.h"
#include "RBEngine/Utils/File.h"

namespace RB
{
	enum class SceneState
	{
		Paused,
		Playing,
		Editing
	};

	enum class SceneDataState
	{
		Synced,
		DeSynced
	};

	class Scene : public std::enable_shared_from_this<Scene>
	{
		friend class SceneSerializer;
	public:
		Scene() = default;
		Scene(const File& path);

		bool Save();
		bool Load();
		Ref<Scene> Copy();

		void OnRuntimeUpdate();
		void OnEditorUpdate(const Camera& camera, const Transform& cameraTransform);

		bool IsValid() const;

		SceneState GetState() { return m_State; }
		SceneDataState GetDataState() { return m_DataState; }
		SceneRegistry& GetRegistry() { return m_Registry; }
		const File& GetPath() const { return m_LocalPath; }

		void SetState(SceneState state) { m_State = state; }
		void SetDataState(SceneDataState state) { m_DataState = state; }

	public:
		static Ref<Scene> Create();
		static Ref<Scene> Create(const File& path);
		
		inline static void SetActive(Ref<Scene> active) { s_Active = active; }
		inline static Ref<Scene>& GetActive() { return s_Active; }
		
	private:
		static Ref<Scene> s_Active;
		SceneRegistry m_Registry;
		File m_LocalPath;

		SceneState m_State;
		SceneDataState m_DataState;
	};
}