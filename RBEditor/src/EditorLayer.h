#pragma once

#include "RBEngine.h"
#include "EditorCamera.h"
#include "RBEditorUI/GUI.h"

namespace RB::Editor
{
	struct EditorContext
	{
		UUID ID{ UUID::INVALID };
		enum class Payloads
		{
			None,
			Entity
		} Payload = Payloads::None;
	};

	class EditorLayer : public Layer, public Singleton<EditorLayer>
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRenderUI() override;

		void PushWindow(EditorWindow* window);
		void PopWindow(EditorWindow* window);

		static void SetEditorCamera(EditorCamera* camera);
		static void SetContext(const EditorContext& context) { Get().m_Context = context; }

		static EditorCamera& GetEditorCamera() { return *Get().m_Camera; }
		static EditorContext& GetContext() { return Get().m_Context; }

	private:
		bool _OnKeyPressed(int key);
		void _SaveScene();

	private:
		EditorContext m_Context;
		EditorCamera* m_Camera;
		std::vector<EditorWindow*> m_Windows;
		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_LastScene;
	};
}