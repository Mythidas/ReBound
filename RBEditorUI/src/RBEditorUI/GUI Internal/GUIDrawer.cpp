#include "GUIDrawer.h"
#include "CustomDrawers.h"
#include "DrawerFactory.h"

namespace RB::Editor::Internal
{
	std::unordered_map<TypeID, DrawerMeta> GUIDrawer::s_Drawers;

	void GUIDrawer::Construct()
	{
		auto vec3Draw = DrawerFactory<Vector3>()
			.Register(Vector3Drawer::Draw);
	}

	void GUIDrawer::RegisterDrawer(const TypeID& id, const DrawerMeta& meta)
	{
		s_Drawers[id] = meta;
	}

	bool GUIDrawer::UseDrawer(const TypeID& id, char* data)
	{
		if (s_Drawers.contains(id))
			return s_Drawers[id].Draw(data);

		return false;
	}
}