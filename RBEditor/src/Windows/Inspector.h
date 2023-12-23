#pragma once

#include "RBEngine.h"
#include "RBEditorUI/GUI.h"

namespace RB::Editor
{
	class Inspector : public EditorWindow
	{
	public:
		virtual void OnGUIRender();

		virtual const char* GetWindowTitle() const { return "Inspector"; }

	private:
		void DrawEntityInfo();
		void DrawVariableInfo(char* data, const VariableMeta& var);
	};
}