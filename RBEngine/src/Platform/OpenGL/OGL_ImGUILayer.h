#pragma once

#include "RBEngine/ImGUI/ImGUILayer.h"

namespace RB::OGL
{
	class OGL_ImGUILayer : public ImGUILayer
	{
	public:
		OGL_ImGUILayer(const Builder& builder);
		~OGL_ImGUILayer();

		virtual void BeginUI() override;
		virtual void EndUI() override;

	private:
		void SetDarkThemeColors();
	};
}