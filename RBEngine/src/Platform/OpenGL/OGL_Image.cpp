#include "rbpch.h"
#include "OGL_Image.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace RB::OGL
{
	namespace Utils
	{
		static GLenum TypeToGL(ImageType type)
		{
			switch (type)
			{
			case ImageType::e1D: return GL_TEXTURE_1D;
			case ImageType::e2D: return GL_TEXTURE_2D;
			case ImageType::e3D: return GL_TEXTURE_3D;
			default: return GL_TEXTURE_2D;
			}
		}

		static GLenum WrapToGL(ImageWrap wrap)
		{
			switch (wrap)
			{
			case ImageWrap::Repeat: return GL_REPEAT;
			case ImageWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
			case ImageWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
		}

		static GLenum TilingToGL(ImageTiling tiling)
		{
			switch (tiling)
			{
			case ImageTiling::Linear: return GL_LINEAR;
			case ImageTiling::Nearest: return GL_NEAREST;
			}
		}

		static GLenum FormatToGL(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return GL_RED;
			case ImageFormat::RGBA8: return GL_RGBA;
			case ImageFormat::RGBA32F: return GL_RGBA;
			}
		}

		static GLenum FormatToGLInternal(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return GL_R8;
			case ImageFormat::RGBA8: return GL_RGBA8;
			case ImageFormat::RGBA32F: return GL_RGBA32F;
			}
		}

		static uint32_t FormatSize(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return 1;
			case ImageFormat::RGBA8: return 4;
			case ImageFormat::RGBA32F: return 4 * 4;
			}

			return 0;
		}

		static void SetGLImage(const Image::Builder& builder)
		{
			if (builder.Type == ImageType::e1D)
			{
				glTexImage1D(GL_TEXTURE_1D, 0, FormatToGL(builder.Format),
					builder.Size.width, 0, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, nullptr);
			}
			else if (builder.Type == ImageType::e2D)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, FormatToGL(builder.Format),
					builder.Size.width, builder.Size.height, 0, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, nullptr);
			}
			else if (builder.Type == ImageType::e3D)
			{
				glTexImage3D(GL_TEXTURE_3D, 0, FormatToGL(builder.Format),
					builder.Size.width, builder.Size.height, builder.Size.depth, 0, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, nullptr);
			}

			glTexParameteri(Utils::TypeToGL(builder.Type), GL_TEXTURE_WRAP_S, Utils::WrapToGL(builder.Wrap));
			glTexParameteri(Utils::TypeToGL(builder.Type), GL_TEXTURE_WRAP_T, Utils::WrapToGL(builder.Wrap));
			glTexParameteri(Utils::TypeToGL(builder.Type), GL_TEXTURE_WRAP_R, Utils::WrapToGL(builder.Wrap));

			glTexParameteri(Utils::TypeToGL(builder.Type), GL_TEXTURE_MIN_FILTER, Utils::TilingToGL(builder.Tiling));
			glTexParameteri(Utils::TypeToGL(builder.Type), GL_TEXTURE_MAG_FILTER, Utils::TilingToGL(builder.Tiling));
		}

		static void SetGLImageData(const Image::Builder& builder, void* data)
		{
			if (builder.Type == ImageType::e1D)
			{
				glTexSubImage1D(GL_TEXTURE_2D, 0, 0, builder.Size.width, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, data);
			}
			else if (builder.Type == ImageType::e2D)
			{
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, builder.Size.width, builder.Size.height, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, data);
			}
			else if (builder.Type == ImageType::e3D)
			{
				glTexSubImage3D(GL_TEXTURE_2D, 0, 0, 0, 0, builder.Size.width, builder.Size.height, builder.Size.depth, FormatToGL(builder.Format), GL_UNSIGNED_BYTE, data);
			}
		}
	}

	OGL_Image::OGL_Image(const Builder& builder)
		: m_RenderID(0)
	{
		glGenTextures(1, &m_RenderID);
		glBindTexture(Utils::TypeToGL(builder.Type), m_RenderID);
		Utils::SetGLImage(builder);
	}

	void OGL_Image::Bind(uint32_t slot) const
	{
		glBindTexture(Utils::TypeToGL(m_Builder.Type), m_RenderID);
		glBindTextureUnit(slot, m_RenderID);
	}

	void OGL_Image::SetData(void* data, size_t size)
	{
		uint32_t imageSize = (m_Builder.Size.x * m_Builder.Size.y * m_Builder.Size.z) * Utils::FormatSize(m_Builder.Format);
		if (size != static_cast<size_t>(imageSize))
		{
			Debug::Log::Error("Size does not match Image Size! Expected: ({0})", imageSize);
			return;
		}

		glBindTexture(Utils::TypeToGL(m_Builder.Type), m_RenderID);
		Utils::SetGLImageData(m_Builder, data);
	}

	// Only supports 2D or 1D texture data
	void OGL_Image::LoadData(const File& path)
	{
		int nrChannels, width, height;
		stbi_set_flip_vertically_on_load(Flipped);
		std::string file = path.ToString();
		unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
		
		glBindTexture(Utils::TypeToGL(m_Builder.Type), m_RenderID);
		Utils::SetGLImage(m_Builder.setSize({ (uint32_t)width, (uint32_t)height, 1 }));
		Utils::SetGLImageData(m_Builder, data);

		stbi_image_free(data);
	}

	void* OGL_Image::GetRenderID() const
	{
		return reinterpret_cast<void*>((uint32_t)m_RenderID);
	}
}