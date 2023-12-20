#pragma once

#include "RBEngine/Rendering/RenderBuffer.h"

namespace RB::OGL
{
	class OGL_RenderBuffer : public RenderBuffer
	{
	public:
		OGL_RenderBuffer(const Builder& builder);

		virtual void Bind() const override;
		virtual void SetData(void* data, size_t size, uint32_t offset) override;
		virtual void* MapBufferPtr(BufferAccess access) override;
		virtual void UnMapBufferPtr() override;

	private:
		Builder m_Builder;
		uint32_t m_RenderID;
	};
}