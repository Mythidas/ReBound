#pragma once

#include "RBEngine/Math/Vector.h"

namespace RB::Editor
{
	class EditorInfo
	{
	public:
		static float LineHeight();
		static float TextPadding();
		static Vector2 ElementPadding();
	};
}