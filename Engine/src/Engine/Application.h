#pragma once

#include "Engine/Core.h"
#include "Engine/Window.h"

#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/LayerStack.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void pushLayer(Layer* t_layer);
		void pushOverlay(Layer* t_overlay);

		void onEvent(Event& t_event);
	private:
		bool onWindowClose(WindowCloseEvent& t_event);
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	//Client defined
	Application* create_application();

}

