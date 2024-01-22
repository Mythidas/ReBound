#include "rbpch.h"
#include "UUID.h"
#include "RBEngine/Math/Mathf.h"

namespace RB
{
	UUID::UUID()
		: m_UUID(Mathf::Random::UInt64())
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}
}