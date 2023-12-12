#pragma once

#include "RBEngine/Core/Window.h"
#include "RBEngine/Rendering/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace RB
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const Window::Builder& specs);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Builder.Width; }
		virtual uint32_t GetHeight() const override { return m_Builder.Height; }

		virtual void SetCursorMode(bool locked) override;

		virtual void* GetNativeWindow() override { return m_Window; }

	private:
		GLFWwindow* m_Window;
		Window::Builder m_Builder;
		Ref<GraphicsContext> m_GraphicsContext;
	};
}