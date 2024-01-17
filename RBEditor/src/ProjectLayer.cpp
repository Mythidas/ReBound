#include "ProjectLayer.h"
#include "RBEditor.h"

#include <imgui.h>

namespace RB::Editor
{
	void ProjectLayer::OnRenderUI()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		bool open = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::Begin("Open Project", &open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

		if (ImGui::Button("New Project"))
		{
			Directory dir = Directory::GetDirectoryDialog();
			if (auto result = Project::NewProject(dir); result & Debug::ResultCode::Success)
			{
				RBEditor::OpenProject();
			}
		}

		if (ImGui::Button("Open Project"))
		{
			File path = File::GetFileDialog({ DialogFilter::Project });
			if (auto result = Project::LoadProject(path); result & Debug::ResultCode::Success)
			{
				RBEditor::OpenProject();
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}
}