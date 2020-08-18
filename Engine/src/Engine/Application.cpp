#include "pch.h"

#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Engine
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{	
		ENGINE_CORE_ASSERT(!s_instance, "Application already exists");
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FCT(Application::onEvent));
		s_instance = this;
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_window->onUpdate();
		}
	}

	void Application::pushLayer(Layer* t_layer)
	{
		m_layerStack.pushLayer(t_layer);
		t_layer->onAttach();
	}

	void Application::pushOverlay(Layer* t_overlay)
	{
		m_layerStack.pushOverlay(t_overlay);
		t_overlay->onAttach();
	}

	//========================== Events ==========================

	void Application::onEvent(Event& t_event)
	{
		EventDispatcher dispatcher(t_event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FCT(Application::onWindowClose));

		ENGINE_CORE_TRACE("{0}", t_event);

		for (auto iterator = m_layerStack.end(); iterator != m_layerStack.begin();)
		{
			(*--iterator)->onEvent(t_event);
			if (t_event.handled)
				break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& t_event)
	{
		m_running = false;
		return true;
	}
}