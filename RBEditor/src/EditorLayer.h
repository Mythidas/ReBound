#pragma once

#include "RBEngine.h"
#include "EditorCamera.h"

namespace RB::Editor
{
	class EditorLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRenderUI() override;

	private:
		EditorCamera m_Camera;
	};
}