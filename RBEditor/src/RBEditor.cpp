#include "RBEditor.h"
#include "RBEngine/Core/EntryPoint.h"
#include "RBEditorUI/GUI Internal/GUIDrawer.h"

namespace RB
{
	RBEditor::RBEditor()
	{
		Editor::Internal::GUIDrawer::Construct();
		m_ProjectLayer = new Editor::ProjectLayer();
		PushLayer(m_ProjectLayer);
	}

	void RBEditor::OpenProject()
	{
		RBEditor* app = static_cast<RBEditor*>(&Get());
		app->PopLayer(app->m_ProjectLayer);
		app->PushLayer(new Editor::EditorLayer());
		delete app->m_ProjectLayer;
	}

	RB::Application* RB::CreateApplication()
	{
		return new RBEditor();
	}
}