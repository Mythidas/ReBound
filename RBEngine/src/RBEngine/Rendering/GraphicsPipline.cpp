#include "rbpch.h"
#include "GraphicsPipline.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_GraphicsPipeline.h"

namespace RB
{
	Ref<GraphicsPipeline> GraphicsPipeline::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_GraphicsPipeline>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}