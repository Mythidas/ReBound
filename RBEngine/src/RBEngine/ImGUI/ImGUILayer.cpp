#include "rbpch.h"
#include "ImGUILayer.h"
#include "RBEngine/Rendering/Renderer.h"
#include "Platform/OpenGL/OGL_ImGUILayer.h"

namespace RB
{
	Ref<ImGUILayer> ImGUILayer::Create(const Builder& builder)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateRef<OGL::OGL_ImGUILayer>(builder);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}