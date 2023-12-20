#pragma once

#include <glm/glm.hpp>

namespace RB
{
	using gVec4 = glm::vec4;

	struct Vector4
	{
		union { float x; float r; float left; };
		union { float y; float g; float right; };
		union { float z; float b; float top; };
		union { float w; float a; float bot; };

		Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		float operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
			if (index == 2)
				return z;
			if (index == 3)
				return w;
		}

		operator glm::vec4() const
		{
			return glm::vec4(x, y, z, w);
		}
	};
}