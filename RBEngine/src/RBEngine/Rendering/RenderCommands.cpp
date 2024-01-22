#include "rbpch.h"
#include "RenderCommands.h"
#include "Renderer.h"
#include "Platform/OpenGL/OGL_RenderCommands.h"

namespace RB
{
	Scope<RenderCommands> RenderCommands::Builder::Build() const
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: RB_ASSERT(false, "RenderAPI::None currently unsupported!"); return nullptr;
		case RenderAPI::OpenGL: return CreateScope<OGL::OGL_RenderCommands>(*this);
		}

		RB_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}