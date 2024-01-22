#include "rbpch.h"
#include "Log.h"
#include "RBEngine/Utils/File.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace RB::Debug
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLog;

	void Debug::Log::Trace(const std::string& message)
	{
		s_ClientLog->trace(message);
	}

	void Debug::Log::Info(const std::string& message)
	{
		s_ClientLog->info(message);
	}

	void Debug::Log::Warn(const std::string& message)
	{
		s_ClientLog->warn(message);
	}

	void Debug::Log::Error(const std::string& message)
	{
		s_ClientLog->error(message);
	}

	void Debug::Log::Critical(const std::string& message)
	{
		s_ClientLog->critical(message);
	}

	void Log::_Construct()
	{
		spdlog::set_pattern("%^[%T] %v%$");

		s_ClientLog = spdlog::stdout_color_mt("App");
		s_ClientLog->set_level(spdlog::level::trace);
	}
}