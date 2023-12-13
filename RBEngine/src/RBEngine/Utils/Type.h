#pragma once

#include <string>

namespace RB
{
	template<typename T>
	class Type
	{
	public:
		Type()
		{
			typedef typename std::remove_reference<T>::type TR;
			m_Type = typeid(TR).name();
		}

		std::string ToString() const
		{
			return m_Type;
		}

	private:
		std::string m_Type;
	};
}