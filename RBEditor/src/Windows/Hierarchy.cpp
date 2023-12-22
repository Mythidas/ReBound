#include "Hierarchy.h"
#include "EditorLayer.h"

#include <imgui.h>

namespace RB::Editor
{
	void Hierarchy::OnGUIRender()
	{
		Ref<Scene> scene = Scene::GetActive();
		if (!scene) return;

		// Right click menu

		if (ImGui::BeginPopupContextWindow("hierarchy_rmb_menu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				scene->GetRegistry().CreateEntity();

			ImGui::EndPopup();
		}

		// Draw Entities

		for (Entity ent : scene->GetRegistry().GetView<Tag>())
		{
			DrawEntityNode(ent);
		}
	}

	void Hierarchy::DrawEntityNode(const Entity& entity)
	{
		Ref<Scene> scene = Scene::GetActive();
		if (!scene) return;

		Tag* tag = entity.GetComponent<Tag>();
		if (ImGui::TreeNode(tag->Name.c_str()))
		{
			ImGui::TreePop();
		}
	}
}