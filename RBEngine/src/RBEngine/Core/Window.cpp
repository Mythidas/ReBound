#include "rbpch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace RB
{
	Event<> Window::OnWindowClose; // No arguments
	Event<int, int> Window::OnWindowResize; // Width, Height
	Event<int> Window::OnKeyPressed; // Key
	Event<int> Window::OnKeyReleased; // Key
	Event<double, double> Window::OnMouseMoved; // Mouse X, Mouse Y
	Event<int> Window::OnMouseButtonPressed; // Button
	Event<int> Window::OnMouseButtonReleased; // Button

	Scope<Window> Window::Create(const Builder& props)
	{
		// TODO: Detect platform and return the correct window
		return CreateScope<WindowsWindow>(props);
	}
}