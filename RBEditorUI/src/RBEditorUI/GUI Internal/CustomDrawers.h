#pragma once

#include "DrawerMeta.h"
#include "RBEngine/Reflection/Meta.h"
#include "RBEngine/Math/Vector.h"

namespace RB::Editor::Internal
{
	class Vector3Drawer : public CustomDrawer<Vector3>
	{
	public:
		static bool Draw(const MetaInfo& meta, char* data);
	};

	class StringDrawer : public CustomDrawer<std::string>
	{
	public:
		static bool Draw(const MetaInfo& meta, char* data);
	};
}