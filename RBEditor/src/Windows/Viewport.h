#pragma once

#include "RBEditorUI/GUI.h"
#include "EditorCamera.h"

namespace RB::Editor
{
	class Viewport : public EditorWindow
	{
	public:
		virtual void OnAttach() override;
		virtual void OnUpdate() override;
		virtual void OnGUIRender() override;

		virtual const char* GetWindowTitle() const { return "Viewport"; }

	private:
		EditorCamera m_Camera;
	};
}