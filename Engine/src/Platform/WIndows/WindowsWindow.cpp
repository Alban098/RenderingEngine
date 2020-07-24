#include "pch.h"
#include "WindowsWindow.h"

namespace Engine 
{
	static bool s_GLFWInitialized = false;

	Window* Window::create(const WindowProperties& t_properties)
	{
		return new WindowsWindow(t_properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& t_properties) {
		init(t_properties);
	}

	WindowsWindow::~WindowsWindow() 
	{
		shutdown();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::init(const WindowProperties& t_properties) 
	{
		m_data.title = t_properties.title;
		m_data.width = t_properties.width;
		m_data.height = t_properties.height;

		ENGINE_INFO("Window {0} of size {1}, {2} is initializing", t_properties.title, t_properties.width, t_properties.height);

		if (!s_GLFWInitialized) 
		{
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success, "GLFW initialization error");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)t_properties.width, (int)t_properties.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::setVSync(bool enabled) 
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapBuffers(0);
		m_data.VSync = enabled;
	}


	bool WindowsWindow::isVSyncEnabled() const
	{
		return m_data.VSync;
	}
}