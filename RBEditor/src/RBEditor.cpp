#include "RBEditor.h"
#include "EditorLayer.h"
#include "RBEngine/Core/EntryPoint.h"

namespace RB
{
	RBEditor::RBEditor()
	{
		PushLayer(new Editor::EditorLayer());
	}

	RB::Application* RB::CreateApplication()
	{
		return new RBEditor();
	}
}