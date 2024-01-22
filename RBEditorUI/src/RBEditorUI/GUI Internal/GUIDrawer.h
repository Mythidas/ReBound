#pragma once

#include "DrawerMeta.h"
#include "RBEngine/Reflection/Type.h"
#include "RBEngine/Reflection/Meta.h"

namespace RB::Editor::Internal
{
	class GUIDrawer
	{
	public:
		static void _Construct();

		static void RegisterDrawer(const TypeID& id, const DrawerMeta& meta);
		static bool UseDrawer(const MetaInfo& meta, char* data);

	private:
		static std::unordered_map<TypeID, DrawerMeta> s_Drawers;
	};
}