#include "CustomDrawers.h"
#include "RBEditorUI/GUI/EditorInfo.h"
#include "RBEditorUI/GUI/Controls.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace RB::Editor::Internal
{
	bool Vector3Drawer::Draw(const MetaInfo& meta, char* data)
	{
		Vector3* vec3 = reinterpret_cast<Vector3*>(data);
		Controls::Vector3(meta.ShortName(), *vec3);
		return true;
	}

	bool StringDrawer::Draw(const MetaInfo& meta, char* data)
	{
		std::string* text = reinterpret_cast<std::string*>(data);
		Controls::Text(meta.ShortName(), *text);
		return true;
	}
}