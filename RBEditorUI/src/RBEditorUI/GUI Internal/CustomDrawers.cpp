#include "CustomDrawers.h"

#include <imgui.h>

namespace RB::Editor::Internal
{
	bool Vector3Drawer::Draw(char* data)
	{
		Vector3 vec3 = static_cast<Vector3>(*data);
		ImGui::Text("Test");
		ImGui::DragFloat("X", &vec3.x);
		ImGui::DragFloat("Y", &vec3.y);
		ImGui::DragFloat("Z", &vec3.z);
		return true;
	}
}