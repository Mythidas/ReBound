#include "rbpch.h"
#include "Image.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_Image.h"

namespace RB
{
	Ref<Image> Image::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_Image>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}