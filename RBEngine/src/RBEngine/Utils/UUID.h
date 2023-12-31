#pragma once

#include <xhash>

namespace RB
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);

		bool operator==(const UUID& rhs) const
		{
			return m_UUID == rhs.m_UUID;
		}

		operator uint64_t() const
		{
			return m_UUID;
		}

	private:
		uint64_t m_UUID;
	};
}

namespace std
{
	template<>
	struct hash<RB::UUID>
	{
		std::size_t operator()(const RB::UUID& uuid) const
		{
			return hash<uint64_t>()(uint64_t(uuid));
		}
	};
}