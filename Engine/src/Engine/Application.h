#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	//Client defined
	Application* create_application();

}

