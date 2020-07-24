#pragma once

#include "Engine/Window.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& t_properties);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		inline void setEventCallback(const EventCallbackFct& t_callback) override { m_data.eventCallback = t_callback; }
		void setVSync(bool t_enabled) override;
		bool isVSyncEnabled() const override;

	private:
		virtual void init(const WindowProperties& t_properties);
		virtual void shutdown();

		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;
			EventCallbackFct eventCallback;
		};

		WindowData m_data;
	};
}

