#include "Viewport.h"
#include "RBEngine.h"

#include <imgui.h>

namespace RB::Editor
{
	void Viewport::OnGUIRender()
	{
		Ref<Framebuffer> buffer = Renderer::GetFramebuffer();
		ImGui::Image((ImTextureID)buffer->GetRenderID(), ImVec2(GetSize().x, GetSize().y));
	}
}