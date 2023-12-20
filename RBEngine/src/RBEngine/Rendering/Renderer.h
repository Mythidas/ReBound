#pragma once

#include "Camera.h"
#include "Framebuffer.h"
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
	public:
		static void Construct();
		static void Destruct();

		static void BeginFrame(const CameraComponent& camera, const TransformComponent& transform);
		static void EndFrame();

		static void DrawQuad(const Vector3& position);

		static void Resize(const UVector2& size);

		static Ref<Framebuffer> GetFramebuffer();
		static RenderAPI GetAPI() { return s_API; }

	private:
		static RenderAPI s_API;
	};
}