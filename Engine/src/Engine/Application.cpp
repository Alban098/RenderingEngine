#include "pch.h"

#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Engine
{
	Application::Application()
	{	
		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			m_window->onUpdate();
		}
	}
}