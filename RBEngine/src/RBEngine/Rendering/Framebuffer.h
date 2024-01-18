#pragma once

#include "RBEngine/Core/Defines.h"
#include "RBEngine/Math/Vector2.h"

namespace RB
{
	class Framebuffer
	{
	public:
		struct Builder
		{
			UVector2 Size;

			Builder& setSize(const UVector2& size) { Size = size; return *this; }
			Ref<Framebuffer> Build() const { return Create(*this); }
		};

		static Ref<Framebuffer> Create(const Builder& builder);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Resize(const UVector2& size) = 0;
		virtual void* GetRenderID() const = 0;
	};
}