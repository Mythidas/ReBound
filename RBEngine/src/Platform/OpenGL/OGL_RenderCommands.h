#pragma once

#include "RBEngine/Rendering/RenderCommands.h"

namespace RB::OGL
{
	class OGL_RenderCommands : public RenderCommands
	{
	public:
		OGL_RenderCommands(const Builder& builder);

		virtual void _ClearColor(const Vector4& color) override;
		virtual void _Resize(const UVector2& size) override;
		virtual void _EnableDepthTesting(bool enable) override;
	};
}