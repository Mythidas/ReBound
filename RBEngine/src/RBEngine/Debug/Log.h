#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace spdlog
{
	class spdlog::logger;
}

namespace RB
{
	class Application;
}

namespace RB::Debug
{
	class Log
	{
	public:
		template <typename... Args>
		inline static void Trace(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			s_ClientLog->trace(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void Info(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			s_ClientLog->info(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void Warn(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			s_ClientLog->warn(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void Error(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			s_ClientLog->error(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void Critical(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			s_ClientLog->critical(message, std::forward<Args>(args)...);
		}

		static void Trace(const std::string& message);
		static void Info(const std::string& message);
		static void Warn(const std::string& message);
		static void Error(const std::string& message);
		static void Critical(const std::string& message);

	private:
		friend class RB::Application;

	private:
		static void _Construct();

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLog;
	};
}