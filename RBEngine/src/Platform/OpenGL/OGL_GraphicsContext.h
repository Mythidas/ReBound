#pragma once

#include "RBEngine/Render/GraphicsContext.h"

namespace RB::OGL
{
	class OGL_GraphicsContext : public GraphicsContext
	{
	public:
		OGL_GraphicsContext(const Builder& builder);

		virtual void SwapBuffers() override;

	private:
		Builder m_Builder;
	};
}