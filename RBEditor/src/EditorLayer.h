#pragma once

#include "RBEngine.h"
#include "EditorCamera.h"
#include "RBEditorUI/EditorWindow.h"

namespace RB::Editor
{
	class EditorLayer : public Layer, public Singleton<EditorLayer>
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRenderUI() override;

		void PushWindow(EditorWindow* window);
		void PopWindow(EditorWindow* window);

		void SetEditorCamera(EditorCamera* camera);

		EditorCamera& GetEditorCamera() { return *m_Camera; }

	private:
		EditorCamera* m_Camera;
		std::vector<EditorWindow*> m_Windows;
	};
}