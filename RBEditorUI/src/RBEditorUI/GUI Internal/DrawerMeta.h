#pragma once

#include "RBEngine/Reflection/Meta.h"

#include <functional>

namespace RB::Editor::Internal
{
	struct DrawerMeta
	{
		std::function<bool(const MetaInfo&, char*)> Draw;
	};

	// Tag to let the compiler know its a CustomDrawer
	template <typename T>
	class CustomDrawer {};
}