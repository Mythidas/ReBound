#include "EditorCamera.h"

namespace RB::Editor
{
	EditorCamera::EditorCamera()
	{
		ClearColor = { 0.4f, 0.5f, 0.6f, 1.0f };
		m_Transform.Position.z = -5.0f;
		Window::OnMouseScrolled += RB_BIND_FNC(OnScroll);
	}

	void EditorCamera::OnUpdate()
	{
		Vector2 mouse = Input::GetMousePosition();
		Vector2 delta = (mouse - m_LastMousePosition) * 0.3f;
		m_LastMousePosition = mouse;

		if (!Input::IsKeyPressed(KeyCode::RightMouseButton))
		{
			Input::LockCursor(false);
			return;
		}

		Input::LockCursor(true);

		// Myth: This is for 3D rotation, don't really need it for 2D. Maybe will make variables to enable it editor
		//m_Transform.Rotation.x -= delta.y;
		//m_Transform.Rotation.y -= delta.x;

		if (Input::IsKeyPressed(KeyCode::W))
		{
			m_Transform.Position += m_Transform.Up() * m_Speed * Time::GetDeltaTime();
		}
		if (Input::IsKeyPressed(KeyCode::S))
		{
			m_Transform.Position += m_Transform.Down() * m_Speed * Time::GetDeltaTime();
		}
		if (Input::IsKeyPressed(KeyCode::A))
		{
			m_Transform.Position += m_Transform.Left() * m_Speed * Time::GetDeltaTime();
		}
		if (Input::IsKeyPressed(KeyCode::D))
		{
			m_Transform.Position += m_Transform.Right() * m_Speed * Time::GetDeltaTime();
		}
	}

	void EditorCamera::OnResize(const UVector2& size)
	{
		if ((size.x != m_Width && size.x > 0) || (size.y != m_Height && size.y > 0))
		{
			m_Width = size.x;
			m_Height = size.y;

			CalculateProjection(m_Width, m_Height);
		}
	}

	bool EditorCamera::OnScroll(float offset)
	{
		if (Input::IsKeyPressed(KeyCode::RightMouseButton))
		{
			m_Transform.Position.z += offset * m_ScrollSpeed * Time::GetDeltaTime();
		}

		return false;
	}
}