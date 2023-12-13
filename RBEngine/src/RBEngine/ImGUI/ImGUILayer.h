#pragma once

#include "RBEngine/Core/Layer.h"
#include "RBEngine/Core/Defines.h"

namespace RB
{
	class ImGUILayer : virtual public Layer
	{
	public:
		struct Builder
		{
			Ref<ImGUILayer> Build() { return Create(*this); }
		};

		virtual void Begin() = 0;
		virtual void End() = 0;

		static Ref<ImGUILayer> Create(const Builder& builder);
	};
}