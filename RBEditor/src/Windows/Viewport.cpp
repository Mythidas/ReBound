#include "Viewport.h"
#include "RBEngine.h"
#include "EditorLayer.h"

#include <imgui.h>

namespace RB::Editor
{
	void Viewport::OnAttach()
	{
		EditorLayer::Get().SetEditorCamera(&m_Camera);
	}

	void Viewport::OnUpdate()
	{
		if (IsHovered())
		{
			m_Camera.OnUpdate();
		}

		m_Camera.OnResize(GetSize());
	}

	void Viewport::OnGUIRender()
	{
		Ref<Framebuffer> buffer = Renderer::GetFramebuffer();
		ImGui::Image((ImTextureID)buffer->GetRenderID(), ImVec2(GetSize().x, GetSize().y));
	}
}