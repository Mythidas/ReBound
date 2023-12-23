#include "RBEditor.h"
#include "EditorLayer.h"
#include "RBEngine/Core/EntryPoint.h"
#include "RBEditorUI/GUI Internal/GUIDrawer.h"

namespace RB
{
	RBEditor::RBEditor()
	{
		Editor::Internal::GUIDrawer::Construct();

		PushLayer(new Editor::EditorLayer());
	}

	RB::Application* RB::CreateApplication()
	{
		return new RBEditor();
	}
}