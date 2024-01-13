#pragma once

#include "RBEngine/Reflection/Type.h"
#include "RBEngine/Math/Vector.h"

namespace RB
{
	struct SpriteRenderer : public Component
	{
		Vector3 Color{ 1.0f, 1.0f, 1.0f };
	};
}