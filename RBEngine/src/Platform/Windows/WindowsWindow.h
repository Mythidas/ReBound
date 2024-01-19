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
		virtual std::string GetTitle() const override { return m_Builder.Title; }
		virtual IVector2 GetWindowPosition() const override;
		virtual WindowState GetWindowState() const override;
		virtual void* GetNativeWindow() override { return m_Window; }

		virtual void SetTitle(const std::string& title) override;
		virtual void SetCursorMode(bool locked) override;
		virtual void SetWindowPosition(const IVector2& pos) override;
		virtual void MinimizeWindow() override;
		virtual void MaximizeWindow() override;

	private:
		GLFWwindow* m_Window;
		Window::Builder m_Builder;
		Ref<GraphicsContext> m_GraphicsContext;
		int m_XWindPosOffset{ 0 };
		int m_YWindPosOffset{ 0 };
	};
}