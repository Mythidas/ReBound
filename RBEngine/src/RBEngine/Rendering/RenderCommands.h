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
			Scope<RenderCommands> Build() const;
		};

		virtual void _ClearColor(const Vector4& color) = 0;
		virtual void _Resize(const UVector2& size) = 0;
		virtual void _EnableDepthTesting(bool enable) = 0;

	public:
		static void ClearColor(const Vector4& color) { Get()._ClearColor(color); }
		static void Resize(const UVector2& size) { Get()._Resize(size); }
		static void EnableDepthTesting(bool enable) { Get()._EnableDepthTesting(enable); }
	};
}