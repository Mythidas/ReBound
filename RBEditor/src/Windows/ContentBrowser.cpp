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

		m_FolderIcon->LoadData("../Assets/icons8-folder.png");
	}

	void ContentBrowser::OnGUIRender()
	{
		static float thumbnailSize = 90.0f;
		ImGui::Image((ImTextureID)m_FolderIcon->GetRenderID(), { thumbnailSize , thumbnailSize });
	}
}