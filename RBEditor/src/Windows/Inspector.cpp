#include "Inspector.h"
#include "EditorLayer.h"
#include "RBEditorUI/GUIInternal.h"
#include "RBEditorUI/GUI.h"

#include <imgui.h>

namespace RB::Editor
{
	void Inspector::OnGUIRender()
	{
		EditorContext context = EditorLayer::GetContext();
		if (context.Payload == EditorContext::Payloads::None) return;
		
		switch (context.Payload)
		{
		case EditorContext::Payloads::Entity: _DrawEntityInfo(); return;
		}
	}

	void Inspector::_DrawEntityInfo()
	{
		EditorContext context = EditorLayer::GetContext();

		auto components = SceneManager::GetActive()->GetRegistry().GetComponents(context.ID);

		for (auto& comp : components)
		{
			char* data = (char*)SceneManager::GetActive()->GetRegistry().GetComponent(context.ID, comp.Info.ID);

			if (comp.Info.ID == Type<Tag>().ID())
			{
				_DrawTag(data);
				continue;
			}

			if (comp.Info.ID == Type<Transform>().ID())
			{
				_DrawTransform(data);
				continue;
			}

			// TODO Myth: Change this to a ImageButton once textures are implemented in engine
			bool node = ImGui::TreeNodeEx(comp.Info.ShortName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding);

			ImGui::SameLine(GetSize().x - 15.0f);
			if (ImGui::Button("R"))
			{
				ImGui::OpenPopup("##RemResComp");
			}

			if (ImGui::BeginPopup("##RemResComp"))
			{
				if (ImGui::MenuItem("Reset Component"))
				{
					SceneManager::GetActive()->GetRegistry().RemoveComponent(context.ID, comp.Info.ID);
					SceneManager::GetActive()->GetRegistry().AddComponent(context.ID, comp.Info.ID);
				}

				if (ImGui::MenuItem("Remove Component"))
				{
					SceneManager::GetActive()->GetRegistry().RemoveComponent(context.ID, comp.Info.ID);
				}

				ImGui::EndPopup();
			}

			if (node)
			{
				if (!Internal::GUIDrawer::UseDrawer(comp.Info, data))
				{
					for (auto& var : comp.Vars)
					{
						_DrawVariableInfo(data, var);
					}
				}

				ImGui::Spacing();
				ImGui::TreePop();
			}

			ImGui::Separator();
		}

		ImGui::Spacing(); ImGui::Spacing();
		if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, EditorInfo::LineHeight())))
			ImGui::OpenPopup("Add Component");

		if (ImGui::BeginPopup("Add Component"))
		{
			for (auto& component : Domain::GetAllComponents())
			{
				if (component.second.Info.ID == Type<Tag>().ID() || component.second.Info.ID == Type<Transform>().ID())
					continue;

				if (SceneManager::GetActive()->GetRegistry().HasComponent(context.ID, component.second.Info.ID))
					continue;

				if (ImGui::MenuItem(component.second.Info.ShortName().c_str()))
				{
					component.second.AddFunc(&SceneManager::GetActive()->GetRegistry(), context.ID);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}
	}

	void Inspector::_DrawVariableInfo(char* data, const VariableMeta& var)
	{
		if (Internal::GUIDrawer::UseDrawer(var.Info, data + var.Offset)) return;

		if (var.Ref == TypeRef::Object)
		{
			auto object = Domain::FindObject(var.Info.ID);

			for (auto& objVar : object.Vars)
			{
				_DrawVariableInfo(data + var.Offset, objVar);
			}
		}
		else if (var.Ref == TypeRef::Float)
		{
			ImGui::DragFloat(var.Info.DebugName.c_str(), (float*)(data + var.Offset));
		}
	}

	void Inspector::_DrawTag(char* data)
	{
		Tag* tag = reinterpret_cast<Tag*>(data);
		ImGui::Spacing();
		Controls::Checkbox("", tag->Active); ImGui::SameLine();
		Controls::Text("", tag->Name);
		ImGui::Spacing();
		ImGui::Separator();
	}

	void Inspector::_DrawTransform(char* data)
	{
		Transform* transform = reinterpret_cast<Transform*>(data);

		bool node = ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding);
		if (node)
		{
			Controls::Vector3("Position", transform->Position);
			Controls::Vector3("Rotation", transform->Rotation);
			Controls::Vector3("Scale", transform->Scale);

			ImGui::Spacing();
			ImGui::TreePop();
		}

		ImGui::Separator();
	}
}