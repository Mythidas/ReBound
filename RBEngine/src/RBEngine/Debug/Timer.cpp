#include "rbpch.h"
#include "Timer.h"

namespace RB
{
	Timer::Timer()
	{
		Reset();
	}

	Timer::Timer(const std::string& name)
	{
		m_Name = name;
		Reset();
	}

	Timer::~Timer()
	{
		if (!m_Name.empty())
			Debug::Log::Info("{0} took {1}ms", m_Name, ElapsedMill());
	}

	void Timer::Reset()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	float Timer::Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_StartTimepoint).count() * 0.001f * 0.001f * 0.001f;
	}

	float Timer::ElapsedMill()
	{
		return Elapsed() * 1000.0f;
	}
}