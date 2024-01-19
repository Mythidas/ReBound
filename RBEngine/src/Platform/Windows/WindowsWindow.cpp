#include "rbpch.h"
#include "WindowsWindow.h"
#include "NativeWindows.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>

namespace RB
{
	WindowsWindow::WindowsWindow(const Window::Builder& specs)
	{
		m_Builder = specs;

		int glfw = glfwInit();
		RB_ASSERT(glfw, "Failed to Init GLFW");

		m_Window = glfwCreateWindow(specs.Width, specs.Height, specs.Title.c_str(), nullptr, nullptr);
		RB_ASSERT(m_Window, "Failed to create GLFW window");

		HWND hWnd = glfwGetWin32Window(m_Window);
		NativeWindows::DisableTitleBar(hWnd);

		glfwMakeContextCurrent(m_Window);

		m_GraphicsContext = GraphicsContext::Builder().setWindowHandle(m_Window).Build();

		glfwSwapInterval((int)specs.VSync);
		glfwSetWindowUserPointer(m_Window, this);

		if (specs.FixedAspectRatio)
			glfwSetWindowAspectRatio(m_Window, specs.Width, specs.Height);

		// Setup Callbacks GLFW

		glfwSetErrorCallback([](int error, const char* desc)
		{
			Debug::Log::Error(desc);
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

		{
			IVector2 cWindPos = GetWindowPosition();
			SetWindowPosition(cWindPos);
			IVector2 nWindPos = GetWindowPosition();
			m_XWindPosOffset = cWindPos.x - nWindPos.x;
			m_YWindPosOffset = cWindPos.y - nWindPos.y;
		}

		Debug::Log::Info("Window Created {0} {1}:{2}", specs.Title, specs.Width, specs.Height);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();

		Debug::Log::Info("WindowsWindow Released");
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_GraphicsContext->SwapBuffers();
	}

	IVector2 WindowsWindow::GetWindowPosition() const
	{
		IVector2 position;
		glfwGetWindowPos(m_Window, &position.x, &position.y);
		return position;
	}

	WindowState WindowsWindow::GetWindowState() const
	{
		if (int state = glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED); state == GLFW_TRUE)
		{
			return WindowState::Fullscreen;
		}
		if (int state = glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED); state == GLFW_TRUE)
		{
			return WindowState::Minimized;
		}

		return WindowState::Windowed;
	}

	void WindowsWindow::SetCursorMode(bool locked)
	{
		if (locked)
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void WindowsWindow::SetWindowPosition(const IVector2& pos)
	{
		glfwSetWindowPos(m_Window, pos.x + m_XWindPosOffset, pos.y + m_YWindPosOffset);
	}

	void WindowsWindow::MinimizeWindow()
	{
		glfwIconifyWindow(m_Window);
	}

	void WindowsWindow::MaximizeWindow()
	{
		if (int maxim = glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED); maxim == GLFW_TRUE)
		{
			glfwRestoreWindow(m_Window);
		}
		else
		{
			glfwMaximizeWindow(m_Window);
		}
	}
}