#include "rbpch.h"
#include "OGL_GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RB::OGL
{
	OGL_GraphicsContext::OGL_GraphicsContext(const Builder& builder)
		: m_Builder(builder)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			RB_ASSERT(false, "Failed to load Glad for OpenGL rendering");
		}
	}

	void OGL_GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_Builder.WindowHandle));
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}