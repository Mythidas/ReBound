#include "rbpch.h"
#include "OGL_Framebuffer.h"

#include <glad/glad.h>

namespace RB::OGL
{
	OGL_Framebuffer::OGL_Framebuffer(const Builder& builder)
	{
		Resize({ 1, 1 });
	}

	OGL_Framebuffer::~OGL_Framebuffer()
	{
		glDeleteFramebuffers(1, &m_RenderID);
		glDeleteTextures(1, &m_Texture);
		glDeleteRenderbuffers(1, &m_RenderObject);
	}

	void OGL_Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);
	}

	void OGL_Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OGL_Framebuffer::Resize(const UVector2& size)
	{
		glDeleteFramebuffers(1, &m_RenderID);
		glDeleteTextures(1, &m_Texture);
		glDeleteRenderbuffers(1, &m_RenderObject);

		glGenFramebuffers(1, &m_RenderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

		glGenRenderbuffers(1, &m_RenderObject);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderObject);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderObject);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Log::Error("Failed to create Framebuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}