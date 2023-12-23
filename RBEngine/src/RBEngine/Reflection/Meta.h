#pragma once

#include "rbpch.h"
#include "Type.h"

namespace RB
{
	struct VariableMeta
	{
		std::string Name;
		std::string TypeID;
		TypeRef Ref;
		size_t Offset;
	};

	struct ObjectMeta
	{
		std::string Name;
		std::vector<VariableMeta> Vars;
		bool Compact{ false };
	};
}