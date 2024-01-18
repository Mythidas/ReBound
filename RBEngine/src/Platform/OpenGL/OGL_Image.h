#pragma once

#include "RBEngine/Rendering/Image.h"

namespace RB::OGL
{
	class OGL_Image : public Image
	{
	public:
		OGL_Image(const Builder& builder);

		virtual void Bind(uint32_t slot) const;
		virtual void SetData(void* data, size_t size);
		virtual void LoadData(const File& path);

		virtual UVector3 GetSize() const { return m_Builder.Size; }
		virtual void* GetRenderID() const;

	private:
		uint32_t m_RenderID;
		Builder m_Builder;
	};
}