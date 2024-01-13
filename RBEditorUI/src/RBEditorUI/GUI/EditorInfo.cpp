#include "EditorInfo.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace RB::Editor
{
	float EditorInfo::LineHeight()
	{
		return GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	}

	float EditorInfo::TextPadding()
	{
		return LineHeight() * 0.15f + ImGui::GetCursorPosY();
	}

	float EditorInfo::ElementPadding()
	{
		return ImGui::GetStyle().WindowPadding.x;
	}
}