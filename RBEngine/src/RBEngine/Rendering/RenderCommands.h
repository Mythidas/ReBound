#pragma once

#include "RBEngine/Core/Defines.h"
#include "RBEngine/Math/Vector.h"
#include "RBEngine/Utils/Singleton.h"

namespace RB
{
	class RenderCommands : public Singleton<RenderCommands>
	{
	public:
		struct Builder
		{
			Scope<RenderCommands> Build() const { return CreateDir(); }
		};

		static void ClearColor(const Color& color) { Get()._ClearColor(color); }
		static void Resize(const UVector2& size) { Get()._Resize(size); }

		static Scope<RenderCommands> CreateDir();

	protected:
		virtual void _ClearColor(const Color& color) = 0;
		virtual void _Resize(const UVector2& size) = 0;
	};
}