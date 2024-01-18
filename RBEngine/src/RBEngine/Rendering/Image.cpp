#include "rbpch.h"
#include "Image.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_Image.h"

namespace RB
{
	Ref<Image> Image::Create(const Builder& builder)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_Image>(builder);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}