#pragma once

#include "RBEngine/ImGUI/ImGUILayer.h"

namespace RB::OGL
{
	class OGL_ImGUILayer : public ImGUILayer
	{
	public:
		OGL_ImGUILayer(const Builder& builder);
		~OGL_ImGUILayer();

		virtual void Begin() override;
		virtual void End() override;

	private:
		void SetDarkThemeColors();
	};
}