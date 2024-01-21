#include "ContentBrowser.h"
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
	}

	void ContentBrowser::OnGUIRender()
	{
		static float thumbnailSize = 90.0f;

		Directory assetDir = Project::GetAssestsDir();

		for (File file : assetDir.GetFilesInDir())
		{
			ImGui::Image((ImTextureID)m_FileIcon->GetRenderID(), { thumbnailSize , thumbnailSize });
		}

		for (Directory dir : assetDir.GetDirectoriesInDir())
		{
			ImGui::Image((ImTextureID)m_FolderIcon->GetRenderID(), { thumbnailSize , thumbnailSize });
			ImGui::Text(dir.Name().c_str());
		}
	}
}