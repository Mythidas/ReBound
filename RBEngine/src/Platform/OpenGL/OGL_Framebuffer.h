#pragma once

#include "RBEngine/Rendering/Framebuffer.h"

namespace RB::OGL
{
	class OGL_Framebuffer : public Framebuffer
	{
	public:
		OGL_Framebuffer(const Builder& builder);
		~OGL_Framebuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Resize(const UVector2& size) override;
		virtual void* GetRenderID() const { return (void*)m_RenderID; }

	private:
		uint32_t m_RenderID{ 0 };
		uint32_t m_Texture{ 0 };
		uint32_t m_RenderObject{ 0 };
	};
}