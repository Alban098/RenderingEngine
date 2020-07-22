#include "pch.h"

#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Engine
{
	Application::Application()
	{	
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		ENGINE_TRACE(e);

		while (true);
	}
}