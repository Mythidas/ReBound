#pragma once

#include "RBEditorUI/EditorWindow.h"

namespace RB::Editor
{
	class Viewport : public EditorWindow
	{
	public:
		virtual void OnGUIRender();

		virtual const char* GetWindowTitle() const { return "Viewport"; }
	};
}