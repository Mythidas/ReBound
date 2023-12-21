#pragma once

#include "RBEngine/Rendering/RenderCommands.h"

namespace RB::OGL
{
	class OGL_RenderCommands : public RenderCommands
	{
	protected:
		virtual void _ClearColor(const Color& color) override;
		virtual void _Resize(const UVector2& size) override;
	};
}