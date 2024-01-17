#pragma once

#include <chrono>

namespace RB
{
	class Timer
	{
	public:
		Timer();
		Timer(const std::string& name);
		~Timer();

		void Reset();
		float Elapsed();
		float ElapsedMill();

	private:
		std::string m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	};
}