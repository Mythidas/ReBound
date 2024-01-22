#include "rbpch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_Framebuffer.h"

namespace RB
{
	Ref<Framebuffer> Framebuffer::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_Framebuffer>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}