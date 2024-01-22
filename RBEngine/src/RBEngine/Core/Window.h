#pragma once

#include "Defines.h"
#include "RBEngine/Math/Vector.h"
#include "RBEngine/Utils/Event.h"

#include <string>

namespace RB
{
	enum class WindowState
	{
		Windowed,
		Minimized,
		Fullscreen
	};

	class Window
	{
	public:
		static Event<> OnWindowClose; // No arguments
		static Event<int, int> OnWindowResize; // Width, Height
		static Event<int> OnKeyPressed; // Key
		static Event<int> OnKeyReleased; // Key
		static Event<double, double> OnMouseMoved; // Mouse X, Mouse Y
		static Event<float> OnMouseScrolled;
		static Event<int> OnMouseButtonPressed; // Button
		static Event<int> OnMouseButtonReleased; // Button

		struct Builder
		{
			Builder& setTitle(const std::string& title) { Title = title; return *this; }
			Builder& setWidth(const uint32_t width) { Width = width; return *this; }
			Builder& setHeight(const uint32_t height) { Height = height; return *this; }
			Builder& setFixedAspectRatio(const bool aspr) { FixedAspectRatio = aspr; return *this; }
			Builder& setVSync(const bool vsync) { VSync = vsync; return *this; }
			Scope<Window> Build() const;

			std::string Title{ "AxtonEngine" };
			uint32_t Width{ 1280 };
			uint32_t Height{ 720 };
			bool FixedAspectRatio{ true };
			bool VSync{ false };
		};

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::string GetTitle() const = 0;
		virtual IVector2 GetWindowPosition() const = 0;
		virtual WindowState GetWindowState() const = 0;
		virtual void* GetNativeWindow() = 0;

		// TODO Myth: Add more cursor modes
		virtual void SetTitle(const std::string& title) = 0;
		virtual void SetCursorMode(bool locked) = 0;
		virtual void SetWindowPosition(const IVector2& pos) = 0;
		virtual void MinimizeWindow() = 0;
		virtual void MaximizeWindow() = 0;
	};
}