#pragma once

#include "RBEngine/Utils/Flags.h"

namespace RB
{
	enum class Result
	{
		Success = 1 << 0,
		Error	= 1 << 1
	};

	RB_FLAG_OPERATORS(Result)
}