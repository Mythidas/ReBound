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
			Ref<GraphicsContext> Build() const;
		};

		virtual void SwapBuffers() = 0;
	};
}