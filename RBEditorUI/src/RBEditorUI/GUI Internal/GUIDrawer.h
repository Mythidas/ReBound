#pragma once

#include "DrawerMeta.h"
#include "RBEngine/Reflection/Type.h"

namespace RB::Editor::Internal
{
	class GUIDrawer
	{
	public:
		static void Construct();

		static void RegisterDrawer(const TypeID& id, const DrawerMeta& meta);
		static bool UseDrawer(const TypeID& id, char* data);

	private:
		static std::unordered_map<TypeID, DrawerMeta> s_Drawers;
	};
}