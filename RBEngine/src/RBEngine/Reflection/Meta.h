#pragma once

#include "Type.h"

#include <vector>

namespace RB
{
	struct MetaInfo
	{
		std::string DebugName;
		TypeID ID;

		std::string ShortName() const
		{
			size_t offset = DebugName.find_last_of(':') + 1;
			return DebugName.substr(offset);
		}
	};

	struct VariableMeta
	{
		MetaInfo Info;
		TypeRef Ref;
		size_t Offset;
	};

	struct ObjectMeta
	{
		MetaInfo Info;
		std::vector<VariableMeta> Vars;
	};
}