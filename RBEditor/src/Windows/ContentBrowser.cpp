#include "ContentBrowser.h"
#include "EditorLayer.h"
#include "RBEngine.h"

#include <imgui.h>

namespace RB::Editor
{
	void ContentBrowser::OnAttach()
	{
		m_FolderIcon = Image::Builder()
			.setType(ImageType::e2D)
			.setFormat(ImageFormat::RGBA8)
			.Build();

		m_FolderIcon->LoadData("../Assets/Textures/icons8-folder.png");

		m_FileIcon = Image::Builder()
			.setType(ImageType::e2D)
			.setFormat(ImageFormat::RGBA8)
			.Build();

		m_FileIcon->LoadData("../Assets/Textures/icons8-file.png");

		m_AssetsDir = Project::GetAssestsDir();
		m_SelectedDir = Project::GetAssestsDir();
	}

	void ContentBrowser::OnGUIRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10.0f);
		{ // Lhs directory tree
			ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
			_DrawDirNode(m_AssetsDir);
			ImGui::EndChild();
		}
		ImGui::PopStyleVar();
		ImGui::SameLine();

		{ // Rhs directory contents
			ImGui::BeginChild("Right pane", ImVec2(ImGui::GetContentRegionAvail().x, 0), ImGuiChildFlags_Border);
			
			{ // Right Click Menu
				if (ImGui::BeginPopupContextWindow("content_rmb_menu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
				{
					if (ImGui::MenuItem("New Scene"))
					{
						Ref<Scene> scene = CreateRef<Scene>((File(m_SelectedDir + "/NewScene.rbscene")));
						scene->Save();
					}

					ImGui::EndPopup();
				}
			}

			ImVec2 cursor = ImGui::GetCursorPos();
			Vector2 vCursor = { cursor.x, cursor.y };
			for (Directory dir : m_SelectedDir.GetDirectoriesInDir())
			{
				_DrawDirEntry(dir, vCursor);
			}

			for (File file : m_SelectedDir.GetFilesInDir())
			{
				_DrawFileEntry(file, vCursor);
			}

			ImGui::EndChild();
		}
		ImGui::SameLine();
	}

	void ContentBrowser::_DrawDirNode(const Directory& dir)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;
		if (!dir.HasDirectories())
			flags |= ImGuiTreeNodeFlags_Leaf;
		if (m_SelectedDir == dir)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		if (_IsChildOpen(dir))
			ImGui::SetNextItemOpen(true);

		bool opened = ImGui::TreeNodeEx(dir.Name().c_str(), flags);

		if (!ImGui::IsItemToggledOpen() && ImGui::IsItemClicked())
			m_SelectedDir = dir;

		if (opened)
		{
			for (Directory child : dir.GetDirectoriesInDir())
				_DrawDirNode(child);

			ImGui::TreePop();
		}
	}

	bool ContentBrowser::_IsChildOpen(const Directory& dir)
	{
		for (Directory child : dir.GetDirectoriesInDir())
		{
			if (child == m_SelectedDir)
				return true;
			else
				if (_IsChildOpen(child))
					return true;
		}

		return false;
	}

	void ContentBrowser::_DrawFileEntry(const File& file, Vector2& cursor)
	{
		ImGui::PushID(file.Name().c_str());
		ImGui::SetCursorPos({ cursor.x, cursor.y });
		if (ImGui::Selectable("##file", false, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_AllowOverlap, { ImGui::GetContentRegionAvail().x, m_ThumbnailSize }))
		{

		}

		if (ImGui::IsItemHovered())
		{
			if (ImGui::IsMouseClicked(0))
			{
				_HandleContextSelection(file);
			}

			if (ImGui::IsMouseDoubleClicked(0))
			{
				_HandleContextOpen(file);
			}
		}

		ImGui::SameLine();
		ImGui::SetNextItemAllowOverlap();
		ImGui::SetCursorPos({ cursor.x + EditorInfo::ElementPadding().x, cursor.y});
		ImGui::Image((ImTextureID)m_FileIcon->GetRenderID(), { m_ThumbnailSize, m_ThumbnailSize });
		ImGui::SameLine();
		ImGui::SetNextItemAllowOverlap();
		ImGui::SetCursorPos({ cursor.x + m_ThumbnailSize + EditorInfo::ElementPadding().x * 2, (cursor.y - EditorInfo::ElementPadding().y * 2) + m_ThumbnailSize / 2 });
		ImGui::Text(file.Name().c_str());
		cursor.y += m_ThumbnailSize + EditorInfo::ElementPadding().y * 2;
		ImGui::PopID();
	}

	void ContentBrowser::_DrawDirEntry(const Directory& dir, Vector2& cursor)
	{
		ImGui::SetCursorPos({ cursor.x, cursor.y });
		if (ImGui::Selectable("##file", false, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_AllowOverlap, { ImGui::GetContentRegionAvail().x, m_ThumbnailSize }))
		{
			if (ImGui::IsMouseDoubleClicked(0))
			{
				m_SelectedDir = dir;
			}
		}
		ImGui::SameLine();
		ImGui::SetNextItemAllowOverlap();
		ImGui::SetCursorPos({ cursor.x + EditorInfo::ElementPadding().x, cursor.y });
		ImGui::Image((ImTextureID)m_FolderIcon->GetRenderID(), { m_ThumbnailSize, m_ThumbnailSize });
		ImGui::SameLine();
		ImGui::SetNextItemAllowOverlap();
		ImGui::SetCursorPos({ cursor.x + m_ThumbnailSize + EditorInfo::ElementPadding().x * 2, (cursor.y - EditorInfo::ElementPadding().y * 2) + m_ThumbnailSize / 2});
		ImGui::Text(dir.Name().c_str());
		cursor.y += m_ThumbnailSize + EditorInfo::ElementPadding().y * 2;
	}

	void ContentBrowser::_HandleContextSelection(const File& file)
	{
		// TODO Myth: Handle selecting files for the inspector
		if (file.Extension() == ".rbscene")
		{
			Debug::Log::Trace("Test");
		}
	}

	void ContentBrowser::_HandleContextOpen(const File& file)
	{
		if (file.Extension() == ".rbscene")
		{
			SceneManager::LoadScene(file);
			SceneManager::GetActive()->SetState(SceneState::Editing);
		}
	}
}