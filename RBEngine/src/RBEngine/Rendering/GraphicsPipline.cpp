#include "rbpch.h"
#include "GraphicsPipline.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_GraphicsPipeline.h"

#include <glad/glad.h>

namespace RB
{
	Ref<GraphicsPipeline> GraphicsPipeline::CreateDir(const Builder& builder)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_GraphicsPipeline>(builder);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}