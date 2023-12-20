#include "rbpch.h"
#include "OGL_RenderBuffer.h"

#include <glad/glad.h>

namespace RB::OGL
{
	namespace Utils
	{
		static GLenum GetBufferUsage(BufferUsage usage)
		{
			switch (usage)
			{
			case BufferUsage::Vertex: return GL_ARRAY_BUFFER;
			case BufferUsage::Index: return GL_ELEMENT_ARRAY_BUFFER;
			case BufferUsage::Uniform: return GL_UNIFORM_BUFFER;
			case BufferUsage::ShaderStorage: return GL_SHADER_STORAGE_BUFFER;
			default: return 0;
			}
		}

		static GLenum GetDrawRate(BufferRate rate)
		{
			switch (rate)
			{
			case BufferRate::Static: return GL_STATIC_DRAW;
			case BufferRate::Dynamic: return GL_DYNAMIC_DRAW;
			default: return 0;
			}
		}

		static GLenum GetBufferAccess(BufferAccess access)
		{
			switch (access)
			{
			case BufferAccess::ReadOnly: return GL_READ_ONLY;
			case BufferAccess::WriteOnly: return GL_WRITE_ONLY;
			case BufferAccess::ReadWrite: return GL_READ_WRITE;
			default: return GL_READ_WRITE;
			}
		}
	}

	OGL_RenderBuffer::OGL_RenderBuffer(const Builder& builder)
		: m_Builder(builder), m_RenderID(0)
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(Utils::GetBufferUsage(builder.Usage), m_RenderID);
		glBufferData(Utils::GetBufferUsage(builder.Usage), builder.Size, nullptr, Utils::GetDrawRate(builder.Rate));

		if (builder.Usage == BufferUsage::Uniform)
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, builder.Binding, m_RenderID, 0, builder.Size);
		}
	}

	void OGL_RenderBuffer::Bind() const
	{
		glBindBuffer(Utils::GetBufferUsage(m_Builder.Usage), m_RenderID);
	}

	void OGL_RenderBuffer::SetData(void* data, size_t size, uint32_t offset)
	{
		if (size + offset > m_Builder.Size)
		{
			Log::Error("Size exceeds allocated RenderBuffer: {0}", m_Builder.Size);
		}

		Bind();
		glNamedBufferSubData(m_RenderID, offset, size, data);
	}

	void* OGL_RenderBuffer::MapBufferPtr(BufferAccess access)
	{
		return glMapNamedBuffer(m_RenderID, Utils::GetBufferAccess(access));
	}

	void OGL_RenderBuffer::UnMapBufferPtr()
	{
		glUnmapNamedBuffer(m_RenderID);
	}
}