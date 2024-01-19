#pragma once

#include <RBEngine/Math/Vector.h>

#include <string>

namespace RB::Editor
{
	class EditorWindow
	{
	public:
		EditorWindow();

		void BeginRender();
		void EndRender();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnGUIRender() {}
		virtual const char* GetWindowTitle() const = 0;

		bool IsFocused() const { return m_IsFocused; }
		bool IsHovered() const { return m_IsHovered; }

		UVector2 GetSize() const { return m_WindowSize; }
		Vector4 GetBounds() const { return m_WindowBounds; }
		Vector2 GetPadding() const { return m_WindowPadding; }
		Vector2 GetCursorPosition() const { return m_CursorPosition; }

		void SetPadding(const Vector2& padding) { m_WindowPadding = padding; }

	private:
		UVector2 m_WindowSize;
		Vector4 m_WindowBounds;
		Vector2 m_WindowPadding;
		Vector2 m_CursorPosition;

		bool m_IsFocused{ false };
		bool m_IsHovered{ false };
	};
}