#pragma once

#include "RBEngine/Core/Defines.h"

namespace RB
{
	class GraphicsContext
	{
	public:
		struct Builder
		{
			void* WindowHandle;

			Builder& setWindowHandle(void* handle) { WindowHandle = handle; return *this; }
			Ref<GraphicsContext> Build() { return Create(*this); }
		};

		virtual void SwapBuffers() = 0;

		static Ref<GraphicsContext> Create(const Builder& builder);
	};
}