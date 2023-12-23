#pragma once

#include "DrawerMeta.h"
#include "GUIDrawer.h"

namespace RB::Editor::Internal
{
	template <typename T>
	class DrawerFactory
	{
	public:
		DrawerMeta Register(std::function<bool(const MetaInfo&, char*)>&& fnc)
		{
			DrawerMeta meta;
			meta.Draw = fnc;
			GUIDrawer::RegisterDrawer(Type<T>().ID(), meta);
			return meta;
		}
	};
}