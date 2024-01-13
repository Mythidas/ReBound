#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace spdlog
{
	class spdlog::logger;
}

namespace RB::Debug
{
	class Log
	{
	public:
		template <typename... Args>
		static void Trace(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			_Initialize();
			s_ClientLog->trace(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		static void Info(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			_Initialize();
			s_ClientLog->info(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		static void Warn(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			_Initialize();
			s_ClientLog->warn(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		static void Error(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			_Initialize();
			s_ClientLog->error(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		static void Critical(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			_Initialize();
			s_ClientLog->critical(message, std::forward<Args>(args)...);
		}

		static void Trace(const char* message);
		static void Info(const char* message);
		static void Warn(const char* message);
		static void Error(const char* message);
		static void Critical(const char* message);

	private:
		static void _Initialize();

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLog;
		static bool s_Initialized;
	};
}