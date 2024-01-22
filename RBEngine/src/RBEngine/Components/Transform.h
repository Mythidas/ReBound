#pragma once

#include "RBEngine/Reflection/Type.h"
#include "RBEngine/Math/Vector.h"
#include "RBEngine/Math/Matrix.h"

namespace RB
{
	struct Transform : public Component
	{
		Vector3 Position{ 0.0f };
		Vector3 Rotation{ 0.0f };
		Vector3 Scale{ 1.0f };

		Vector3 Forward() const;
		Vector3 Back() const;
		Vector3 Right() const;
		Vector3 Left() const;
		Vector3 Up() const;
		Vector3 Down() const;
		Matrix4 GetMatrix() const;
		Matrix4 GetInverseMatrix() const;
	};
}