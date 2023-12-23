#pragma once

#include "EntityEntry.h"

#include <string>

namespace RB
{
	class ComponentPool
	{
	public:
		ComponentPool(const std::string& type, size_t size)
			: m_Type(type), m_ComponentSize(size)
		{
			m_Data = new char[size * MAX_ENTITIES];
		}

		~ComponentPool()
		{
			delete[] m_Data;
		}

		std::string GetType() const
		{
			return m_Type;
		}

		inline void* GetData(size_t index)
		{
			return m_Data + index * m_ComponentSize;
		}

		bool IsType(const std::string& type) const
		{
			return m_Type == type;
		}

	private:
		std::string m_Type;
		size_t m_ComponentSize;
		char* m_Data;
	};
}