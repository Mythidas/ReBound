#pragma once

#include "SpriteRenderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "RBEngine/Scene/Transform.h"
#include "Image.h"
#include "RBEngine/Math/Matrix.h"

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

		static void DrawQuad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color);
		static void DrawQuad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color, Ref<Image> texture);
		static void DrawQuad(const Matrix4& transform, const Vector3& color, float textureID);
		static void DrawQuad(const Matrix4& transform, const Vector3& color, Vector2 texCoords[4], float textureID);

		static void Resize(const UVector2& size);

		static Ref<Framebuffer> GetFramebuffer();
		static RenderAPI GetAPI() { return s_API; }

	private:
		static void _CheckBatch();
		static void _BeginBatch();
		static void _EndBatch();
		static float _GetTextureIndex(Ref<Image> texture);

	private:
		static RenderAPI s_API;
	};
}