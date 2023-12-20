#include "rbpch.h"
#include "RenderBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_RenderBuffer.h"

#include <glad/glad.h>

namespace RB
{
	Ref<RenderBuffer> RenderBuffer::Create(const Builder& builder)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_RenderBuffer>(builder);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}