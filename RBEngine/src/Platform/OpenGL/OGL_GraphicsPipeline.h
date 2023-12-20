#pragma once

#include "RBEngine/Rendering/GraphicsPipline.h"

namespace RB::OGL
{
	class OGL_GraphicsPipeline : public GraphicsPipeline
	{
	public:
		OGL_GraphicsPipeline(const Builder& builder);

		virtual void Draw(uint32_t count) const override;

	private:
		Builder m_Builder;
		uint32_t m_RenderID;
		uint32_t m_VertexID;
	};
}