#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Window.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& t_event);
	private:
		bool onWindowClose(WindowCloseEvent& t_event);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	//Client defined
	Application* create_application();

}

