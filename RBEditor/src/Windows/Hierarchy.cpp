#include "Hierarchy.h"
#include "EditorLayer.h"

#include <imgui.h>

namespace RB::Editor
{
	void Hierarchy::OnGUIRender()
	{
		Ref<Scene> scene = SceneManager::GetActive();
		if (!scene || !scene->IsValid()) return;

		// Deselect

		if (Input::IsKeyPressed(KeyCode::LeftMouseButton) && IsHovered() && !ImGui::IsAnyItemHovered())
			EditorLayer::SetContext({});

		// Right click menu

		if (ImGui::BeginPopupContextWindow("hierarchy_rmb_menu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				scene->GetRegistry().CreateEntity();
				scene->SetDataState(SceneDataState::DeSynced);
			}

			ImGui::EndPopup();
		}

		// Draw Entities

		for (Entity ent : scene->GetRegistry().GetView<Tag>())
		{
			_DrawEntityNode(ent);
		}
	}

	void Hierarchy::_DrawEntityNode(Entity& entity)
	{
		Ref<Scene> scene = SceneManager::GetActive();
		if (!scene) return;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_FramePadding;
		if (EditorLayer::GetContext().ID == entity)
			flags |= ImGuiTreeNodeFlags_Selected;

		Tag* tag = entity.GetComponent<Tag>();
		bool opened = ImGui::TreeNodeEx((void*)tag->Name.c_str(), flags, tag->Name.c_str());

		if (ImGui::IsItemHovered() && Input::IsKeyPressed(KeyCode::LeftMouseButton))
			EditorLayer::SetContext({ entity, EditorPayload::Entity });

		if (ImGui::BeginPopupContextItem(0, ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonRight))
		{
			EditorLayer::SetContext({ entity, EditorPayload::Entity });

			if (ImGui::MenuItem("Delete Entity"))
				entity.Destroy();

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}
}