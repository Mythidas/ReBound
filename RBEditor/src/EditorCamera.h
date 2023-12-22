#pragma once

#include "RBEngine.h"

namespace RB::Editor
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();

		void OnUpdate();
		void OnResize(const UVector2& size);

		Transform& GetTransform() { return m_Transform; }
		
	private:
		bool OnScroll(float offset);

	private:
		Transform m_Transform{};
		Vector2 m_LastMousePosition{ 0.0f };
		uint32_t m_Width{ 1 };
		uint32_t m_Height{ 1 };
		float m_Speed{ 3.0f };
		float m_ScrollSpeed{ 400.0f };
	};
}