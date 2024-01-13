#pragma once

#include "SpriteRenderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "RBEngine/Scene/Transform.h"

namespace RB
{
	enum class RenderAPI
	{
		None,
		OpenGL
	};

	class Renderer
	{
	private:
		friend class Application;
		static void Construct();
		static void Destruct();

	public:
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