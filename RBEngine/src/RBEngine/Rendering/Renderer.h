#pragma once

#include "RBEngine/Math/Vector.h"

namespace RB
{
	enum class RenderAPI
	{
		None,
		OpenGL
	};

	class Renderer
	{
	public:
		static void Construct();
		static void Destruct();

		static void BeginFrame();
		static void EndFrame();

		static void DrawQuad(Vector3 position);

		static RenderAPI GetAPI() { return s_API; }

	private:
		static RenderAPI s_API;
	};
}