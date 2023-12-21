#include "rbpch.h"
#include "OGL_RenderCommands.h"

#include <glad/glad.h>

namespace RB::OGL
{
	void OGL_RenderCommands::_ClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OGL_RenderCommands::_Resize(const UVector2& size)
	{
		glViewport(0, 0, size.x, size.y);
	}
}