#include "rbpch.h"
#include "WindowsWindow.h"

namespace RB
{
	WindowsWindow::WindowsWindow(const Window::Builder& specs)
	{
		m_Builder = specs;

		int glfw = glfwInit();
		RB_ASSERT(glfw, "Failed to Init GLFW");


		m_Window = glfwCreateWindow(specs.Width, specs.Height, specs.Title.c_str(), nullptr, nullptr);
		RB_ASSERT(m_Window, "Failed to create GLFW window");

		glfwMakeContextCurrent(m_Window);

		m_GraphicsContext = GraphicsContext::Builder().setWindowHandle(m_Window).Build();

		glfwSwapInterval((int)specs.VSync);
		glfwSetWindowUserPointer(m_Window, this);

		if (specs.FixedAspectRatio)
			glfwSetWindowAspectRatio(m_Window, specs.Width, specs.Height);

		// Setup Callbacks GLFW

		glfwSetErrorCallback([](int error, const char* desc)
		{
			Log::Error(desc);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Window::OnWindowClose();
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsWindow* wWindow = ((WindowsWindow*)glfwGetWindowUserPointer(window));
			wWindow->m_Builder.Width = width;
			wWindow->m_Builder.Height = height;

			Window::OnWindowResize(width, height);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
				Window::OnKeyPressed(key);
			else if (action == GLFW_RELEASE)
				Window::OnKeyReleased(key);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Window::OnMouseMoved(xpos, ypos);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Window::OnMouseScrolled((float)yoffset);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				Window::OnMouseButtonPressed(button);
			}
			else if (action == GLFW_RELEASE)
				Window::OnMouseButtonReleased(button);
		});

		Log::Info("Window Created {0} {1}:{2}", specs.Title, specs.Width, specs.Height);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();

		Log::Info("WindowsWindow Released");
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_GraphicsContext->SwapBuffers();
	}

	void WindowsWindow::SetCursorMode(bool locked)
	{
		if (locked)
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}