#pragma once

#include "RBEngine/Utils/Flags.h"

namespace RB::Debug
{
	enum class ResultCode
	{
		Success =	1 << 0,
		Error =		1 << 1,
		Invalid =	1 << 2
	};

	RB_FLAG_OPERATORS(ResultCode)

	struct Result
	{
		ResultCode Code;
		std::string Message;

		Result(ResultCode code) : Code(code) {}
		Result(ResultCode code, std::string message) : Code(code), Message(message) {}

		operator ResultCode() const
		{
			return Code;
		}

		operator std::string() const
		{
			return Message;
		}
	};
}