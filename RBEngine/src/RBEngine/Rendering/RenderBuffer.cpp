#include "rbpch.h"
#include "RenderBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_RenderBuffer.h"

namespace RB
{
	Ref<RenderBuffer> RenderBuffer::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_RenderBuffer>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}