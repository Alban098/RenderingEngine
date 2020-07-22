#include "pch.h"

#include "Log.h"

namespace Engine
{
	std::shared_ptr <spdlog::logger> Log::s_core_logger_;
	std::shared_ptr <spdlog::logger> Log::s_client_logger_;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_core_logger_ = spdlog::stdout_color_mt("Core");
		s_core_logger_->set_level(spdlog::level::trace);
		
		s_client_logger_ = spdlog::stdout_color_mt("App");
		s_client_logger_->set_level(spdlog::level::trace);
	}
}
