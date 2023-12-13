#pragma once

#include "Entity.h"

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

		bool IsType(const std::string& type)
		{
			return m_Type == type;
		}

		inline void* GetData(size_t index)
		{
			return m_Data + index * m_ComponentSize;
		}

	private:
		std::string m_Type;
		size_t m_ComponentSize;
		char* m_Data;
	};
}