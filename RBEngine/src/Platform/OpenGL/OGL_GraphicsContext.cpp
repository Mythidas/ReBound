#include "rbpch.h"
#include "OGL_GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RB::OGL
{
	OGL_GraphicsContext::OGL_GraphicsContext(const Builder& builder)
		: m_Builder(builder)
	{
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void OGL_GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_Builder.WindowHandle));
	}
}