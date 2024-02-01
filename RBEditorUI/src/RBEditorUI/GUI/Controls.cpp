#include "Controls.h"
#include "EditorInfo.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace RB::Editor
{
	void Controls::Text(const std::string& label, std::string& value)
	{
		_DrawLabel(label);
		ImGui::InputText("##Text", &value);
	}

	void Controls::Checkbox(const std::string& label, bool& checked)
	{
		ImGui::Checkbox("##Checkbox", &checked);
		ImGui::SameLine();
		_DrawLabel(label);
	}

	void Controls::ButtonCombo(const std::string& label, int& index, std::vector<const char*> values)
	{

	}

	void Controls::ButtonComboFiltered(const std::string& label, int& index, std::vector<const char*> values, const char* filter)
	{

	}

	void Controls::Vector3(const std::string& label, RB::Vector3& vec3)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		_DrawLabel(label);

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, ImGui::GetContentRegionAvail().x / 3.33f);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushFont(boldFont);
		ImGui::Button("X", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &vec3.x, 0.05f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushFont(boldFont);
		ImGui::Button("Y", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &vec3.y, 0.05f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushFont(boldFont);
		ImGui::Button("Z", buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &vec3.z, 0.05f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void Controls::_DrawLabel(const std::string& label)
	{
		if (label.empty()) return;
		ImGui::SetCursorPosY(EditorInfo::TextPadding());
		ImGui::Text(label.c_str());
	}

	void Controls::_SetPadding(float padding)
	{
		if (padding == 0)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + EditorInfo::ElementPadding().x);
		else
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding);
	}
}