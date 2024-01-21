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
		void _DrawDirNode(const Directory& dir);
		bool _IsChildOpen(const Directory& dir);
		void _DrawFileEntry(const File& file, Vector2& cursor);
		void _DrawDirEntry(const Directory& dir, Vector2& cursor);
		void _HandleContextSelection(const File& file);

	private:
		Ref<Image> m_FolderIcon;
		Ref<Image> m_FileIcon;
		Directory m_SelectedDir;
		Directory m_AssetsDir;
		float m_ThumbnailSize{ 24.0f };
	};
}