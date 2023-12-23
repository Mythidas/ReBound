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
			char* data = (char*)Scene::GetActive()->GetRegistry().GetComponent(context.ID, comp.Object.Name);

			if (ImGui::TreeNode(comp.Object.Name.c_str()))
			{
				for (auto& var : comp.Object.Vars)
				{
					DrawVariableInfo(data, var);
				}

				ImGui::TreePop();
			}
		}
	}

	void Inspector::DrawVariableInfo(char* data, const VariableMeta& var)
	{
		if (Internal::GUIDrawer::UseDrawer(var.TypeID, data)) return;

		if (var.Ref == TypeRef::Object)
		{

			auto object = Domain::FindObject(var.TypeID);

			ImGui::Text(var.Name.c_str());
			for (auto& objVar : object.Vars)
			{
				DrawVariableInfo(data + var.Offset, objVar);
			}
		}
		else if (var.Ref == TypeRef::Float)
		{
			ImGui::DragFloat(var.Name.c_str(), (float*)(data + var.Offset));
		}
	}
}