#pragma once

#include <RBEngine.h>

namespace RB::Editor
{
	class ProjectLayer : public Layer
	{
	public:
		virtual void OnRenderUI() override;
	};
}