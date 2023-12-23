#pragma once

#include "DrawerMeta.h"
#include "RBEngine/Math/Vector.h"

namespace RB::Editor::Internal
{
	class Vector3Drawer : public CustomDrawer<Vector3>
	{
	public:
		static bool Draw(char* data);
	};
}