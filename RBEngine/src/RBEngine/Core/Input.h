#pragma once

#include "Defines.h"
#include "KeyCodes.h"
#include "RBEngine/Utils/Singleton.h"
#include "RBEngine/Math/Vector.h"

namespace RB
{
	class Input : public Singleton<Input>
	{
	public:
		Input();

		static bool IsKeyPressed(Key key);
		static bool IsKeyReleased(Key key);
		static Vector2 GetMousePosition();

		static void LockCursor(bool lock);

	private:
		static bool s_Keys[352];
		static Vector2 s_MousePosition;

		static bool onKeyPressed(int key);
		static bool onKeyReleased(int key);
		static bool onMouseMoved(double x, double y);
		static bool onMouseButtonPressed(int button);
		static bool onMouseButtonReleased(int button);
	};
}