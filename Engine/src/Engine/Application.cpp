#include "pch.h"

#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Engine
{

#define BIND_EVENT_FCT(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{	
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FCT(Application::onEvent));
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
	//========================== Events ==========================

	void Application::onEvent(Event& t_event)
	{
		EventDispatcher dispatcher(t_event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FCT(Application::onWindowClose));

		ENGINE_CORE_TRACE("{0}", t_event);
	}

	bool Application::onWindowClose(WindowCloseEvent& t_event)
	{
		m_running = false;
		return true;
	}
}