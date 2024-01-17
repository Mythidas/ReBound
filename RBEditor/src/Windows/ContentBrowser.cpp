#include "ContentBrowser.h"
#include "RBEngine.h"

#include <imgui.h>

namespace RB::Editor
{
	void ContentBrowser::OnGUIRender()
	{
		ImGui::Text(Project::GetAssestsDir().ToString().c_str());
	}
}