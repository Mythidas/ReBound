#pragma once

#include "EditorLayer.h"
#include "ProjectLayer.h"

#include <RBEngine.h>

namespace RB
{
	class RBEditor : public Application
	{
	public:
		RBEditor();

		static void OpenProject();

	private:
		Editor::ProjectLayer* m_ProjectLayer;
	};
}