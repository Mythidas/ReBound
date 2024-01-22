#pragma once

#include "RBEngine/Reflection/Type.h"

#include <string>

namespace RB
{
	struct Tag : public Component
	{
		std::string Name;
		bool Active{ true };
	};
}