#pragma once

#include "RBEngine.h"
#include "RBEditorUI/GUI.h"

namespace RB::Editor
{
	class Hierarchy : public EditorWindow
	{
	public:
		virtual void OnGUIRender();

		virtual const char* GetWindowTitle() const { return "Hierarchy"; }

	private:
		void _DrawEntityNode(Entity& entity);
	};
}