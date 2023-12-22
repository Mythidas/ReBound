#pragma once

#include "RenderComps.h"
#include "Framebuffer.h"
#include "RBEngine/Scene/SceneComps.h"

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

		static void BeginFrame(const Camera& camera, const Transform& transform);
		static void EndFrame();

		static void DrawQuad(const Vector3& position);
		static void DrawQuad(const Transform& transform, const SpriteRenderer& sprite);

		static void Resize(const UVector2& size);

		static Ref<Framebuffer> GetFramebuffer();
		static RenderAPI GetAPI() { return s_API; }

	private:
		static RenderAPI s_API;
	};
}