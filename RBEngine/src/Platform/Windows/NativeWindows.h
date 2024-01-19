#pragma once

#include <Windows.h>

namespace RB
{
	class NativeWindows
	{
	public:
		static void DisableTitleBar(HWND hWnd);
	};
}