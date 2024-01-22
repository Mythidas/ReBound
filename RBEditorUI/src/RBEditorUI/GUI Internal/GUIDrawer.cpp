#include "GUIDrawer.h"
#include "CustomDrawers.h"
#include "DrawerFactory.h"

namespace RB::Editor::Internal
{
	std::unordered_map<TypeID, DrawerMeta> GUIDrawer::s_Drawers;

	void GUIDrawer::_Construct()
	{
		auto vec3Draw = DrawerFactory<Vector3>()
			.Register(Vector3Drawer::Draw);
		auto strDraw = DrawerFactory<std::string>()
			.Register(StringDrawer::Draw);
	}

	void GUIDrawer::RegisterDrawer(const TypeID& id, const DrawerMeta& meta)
	{
		s_Drawers[id] = meta;
	}

	bool GUIDrawer::UseDrawer(const MetaInfo& meta, char* data)
	{
		if (s_Drawers.contains(meta.ID))
			return s_Drawers[meta.ID].Draw(meta, data);

		return false;
	}
}