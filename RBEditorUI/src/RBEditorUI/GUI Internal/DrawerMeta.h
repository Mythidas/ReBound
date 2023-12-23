#pragma once

#include <functional>

namespace RB::Editor::Internal
{
	struct DrawerMeta
	{
		std::function<bool(char*)> Draw;
	};

	// Tag to let the compiler know its a CustomDrawer
	template <typename T>
	class CustomDrawer {};
}