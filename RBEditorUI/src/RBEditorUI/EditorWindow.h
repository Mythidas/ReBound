#pragma once

#include <RBEngine/Math/Vector.h>

#include <string>

namespace RB::Editor
{
	class EditorWindow
	{
	public:
		void BeginRender();
		void EndRender();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnGUIRender() {};
		virtual const char* GetWindowTitle() const = 0;

		Vector2 GetSize() const { return m_WindowSize; }
		Vector4 GetBounds() const { return m_WindowBounds; }
		Vector2 GetCursorPosition() const { return m_CursorPosition; }

	private:
		Vector2 m_WindowSize;
		Vector4 m_WindowBounds;
		Vector2 m_CursorPosition;

		bool m_IsFocused{ false };
		bool m_IsHovered{ false };
	};
}