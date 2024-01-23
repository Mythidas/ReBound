#pragma once

#include "SceneRegistry.h"
#include "RBEngine/Components/Camera.h"
#include "RBEngine/Components/Transform.h"
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
	public:
		Scene() = default;
		Scene(const File& path);

		bool Save();
		bool Load();
		Ref<Scene> Copy();

		void OnUpdate(Camera* camera, Transform* transform);

		bool IsValid() const;

		SceneState GetState() { return m_State; }
		SceneDataState GetDataState() { return m_DataState; }
		SceneRegistry& GetRegistry() { return m_Registry; }
		const File& GetPath() const { return m_LocalPath; }

		void SetState(SceneState state) { m_State = state; }
		void SetDataState(SceneDataState state) { m_DataState = state; }
		
	private:
		friend class SceneSerializer;

	private:
		SceneRegistry m_Registry;
		File m_LocalPath;

		SceneState m_State;
		SceneDataState m_DataState;
	};
}