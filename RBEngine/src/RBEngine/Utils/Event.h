#pragma once

#include <functional>

namespace RB
{
	template <typename... Args>
	class Event
	{
	private:
		using Func = std::function<bool(Args...)>;

	public:
		void operator()(Args... args)
		{
			for (auto& callback : m_Callbacks)
			{
				if (callback(args...))
					break;
			}
		}

		void operator +=(const Func& callback)
		{
			m_Callbacks.push_back(callback);
		}

	private:
		std::vector<Func> m_Callbacks;
	};
}