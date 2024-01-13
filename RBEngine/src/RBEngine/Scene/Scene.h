#pragma once

#include "Transform.h"
#include "EntityRegistry.h"
#include "RBEngine/Rendering/Camera.h"

namespace RB
{
	class Scene
	{
	public:
		void OnRuntimeUpdate();
		void OnEditorUpdate(const Camera& camera, const Transform& cameraTransform);

		EntityRegistry& GetRegistry() { return m_Registry; }

		static Ref<Scene>& GetActive() { return s_Active; }
		static Ref<Scene> Create();
		
	private:
		static Ref<Scene> s_Active;

		EntityRegistry m_Registry;
	};
}