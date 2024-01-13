#include "rbpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace RB::Debug
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLog;
	bool Log::s_Initialized = false;

	void Debug::Log::Trace(const char* message)
	{
		_Initialize();
		s_ClientLog->trace(message);
	}

	void Debug::Log::Info(const char* message)
	{
		_Initialize();
		s_ClientLog->info(message);
	}

	void Debug::Log::Warn(const char* message)
	{
		_Initialize();
		s_ClientLog->warn(message);
	}

	void Debug::Log::Error(const char* message)
	{
		_Initialize();
		s_ClientLog->error(message);
	}

	void Debug::Log::Critical(const char* message)
	{
		_Initialize();
		s_ClientLog->critical(message);
	}

	void Log::_Initialize()
	{
		if (s_Initialized) return;

		spdlog::set_pattern("%^[%T] %v%$");

		s_ClientLog = spdlog::stdout_color_mt("App");
		s_ClientLog->set_level(spdlog::level::trace);
		s_Initialized = true;
	}
}