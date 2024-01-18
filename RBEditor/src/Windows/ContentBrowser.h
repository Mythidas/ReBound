#pragma once

#include "RBEngine.h"
#include "RBEditorUI/GUI.h"

namespace RB::Editor
{
	class ContentBrowser : public EditorWindow
	{
	public:
		virtual void OnAttach() override;
		virtual void OnGUIRender() override;

		virtual const char* GetWindowTitle() const { return "ContentBrowser"; }

	private:
		Ref<Image> m_FolderIcon;
		Ref<Image> m_FileIcon;
	};
}