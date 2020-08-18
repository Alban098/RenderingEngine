#include "pch.h"
#include "WindowsWindow.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Engine 
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int t_error, const char* t_desc) 
	{
		ENGINE_CORE_ERROR("GLFW Error {0} : {1}", t_error, t_desc);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)t_properties.width, (int)t_properties.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Glad initialization failed");
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		//Callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});
	
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_offset, double y_offset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x_offset, (float)y_offset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.eventCallback(event);
		});
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