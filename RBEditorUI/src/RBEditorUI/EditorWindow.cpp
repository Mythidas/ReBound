#include "EditorWindow.h"

#include <imgui.h>

namespace RB::Editor
{
	void EditorWindow::BeginRender()
	{
		ImGui::Begin(GetWindowTitle());

		ImVec2 windowSize = ImGui::GetContentRegionAvail();
		m_WindowSize = { windowSize.x, windowSize.y };

		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		ImVec2 wPos = ImGui::GetWindowPos();

		vMin.x += wPos.x;
		vMin.y += wPos.y;
		vMax.x += wPos.x;
		vMax.y += wPos.y;

		m_WindowBounds = { vMin.x, vMin.y, vMax.x, vMax.y };

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_WindowBounds.x;
		my -= m_WindowBounds.w;

		m_CursorPosition = { mx, -my };

		m_IsFocused = ImGui::IsWindowFocused();
		m_IsHovered = ImGui::IsWindowHovered();
	}

	void EditorWindow::EndRender()
	{
		ImGui::End();
	}
}