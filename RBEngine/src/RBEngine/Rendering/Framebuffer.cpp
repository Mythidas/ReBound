#include "rbpch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_Framebuffer.h"

namespace RB
{
	Ref<Framebuffer> Framebuffer::CreateDir(const Builder& builder)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_Framebuffer>(builder);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}