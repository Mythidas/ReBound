#include "rbpch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_GraphicsContext.h"

namespace RB
{
	Ref<GraphicsContext> GraphicsContext::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_GraphicsContext>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}