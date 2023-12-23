#pragma once

#include "RBEditorUI/GUI.h"

namespace RB::Editor
{
	class ContentBrowser : public EditorWindow
	{
	public:
		virtual void OnGUIRender();

		virtual const char* GetWindowTitle() const { return "ContentBrowser"; }
	};
}