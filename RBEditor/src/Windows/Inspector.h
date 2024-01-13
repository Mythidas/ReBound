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
		void _DrawEntityInfo();
		void _DrawTag(char* data);
		void _DrawVariableInfo(char* data, const VariableMeta& var);
	};
}