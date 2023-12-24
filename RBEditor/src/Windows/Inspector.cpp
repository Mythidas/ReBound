#include "Inspector.h"
#include "EditorLayer.h"
#include "RBEditorUI/GUIInternal.h"

#include <imgui.h>

namespace RB::Editor
{
	void Inspector::OnGUIRender()
	{
		EditorContext context = EditorLayer::GetContext();
		if (context.Payload == EditorContext::Payloads::None) return;
		
		switch (context.Payload)
		{
		case EditorContext::Payloads::Entity: DrawEntityInfo(); return;
		}
	}

	void Inspector::DrawEntityInfo()
	{
		EditorContext context = EditorLayer::GetContext();

		auto components = Scene::GetActive()->GetRegistry().GetComponents(context.ID);

		for (auto& comp : components)
		{
			char* data = (char*)Scene::GetActive()->GetRegistry().GetComponent(context.ID, comp.Object.Info.ID);

			if (ImGui::TreeNode(comp.Object.Info.ShortName().c_str()))
			{
				if (Internal::GUIDrawer::UseDrawer(comp.Object.Info, data)) return;

				for (auto& var : comp.Object.Vars)
				{
					DrawVariableInfo(data, var);
				}

				ImGui::TreePop();
			}
		}

		ImGui::Spacing();
		if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, EditorInfo::LineHeight())))
			ImGui::OpenPopup("Add Component");

		if (ImGui::BeginPopup("Add Component"))
		{
			for (auto& component : EntityRegistry::GetRegisteredComponents())
			{
				if (component.second.Object.Info.ID == Type<Tag>().ID() || component.second.Object.Info.ID == Type<Transform>().ID())
					continue;

				if (Scene::GetActive()->GetRegistry().HasComponent(context.ID, component.second.Object.Info.ID))
					continue;

				if (ImGui::MenuItem(component.second.Object.Info.DebugName.c_str()))
				{
					component.second.AddFunc(&Scene::GetActive()->GetRegistry(), context.ID);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}
	}

	void Inspector::DrawVariableInfo(char* data, const VariableMeta& var)
	{
		if (Internal::GUIDrawer::UseDrawer(var.Info, data + var.Offset)) return;

		if (var.Ref == TypeRef::Object)
		{
			auto object = Domain::FindObject(var.Info.ID);

			for (auto& objVar : object.Vars)
			{
				DrawVariableInfo(data + var.Offset, objVar);
			}
		}
		else if (var.Ref == TypeRef::Float)
		{
			ImGui::DragFloat(var.Info.DebugName.c_str(), (float*)(data + var.Offset));
		}
	}
}