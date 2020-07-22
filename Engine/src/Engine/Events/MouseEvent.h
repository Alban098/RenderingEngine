#pragma once

#include "Event.h"

namespace Engine 
{
	class ENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float t_x, float t_y) 
			: m_mouse_x(t_x), m_mouse_y(t_y) {}

		inline float getMouseX() const { return m_mouse_x; }
		inline float getMouseY() const { return m_mouse_y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouse_x << ", " << m_mouse_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_mouse_x, m_mouse_y;
	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float t_x_offset, float t_y_offset) 
			: m_offset_x(t_x_offset), m_offset_y(t_y_offset) {}

		inline float getOffsetX() const { return m_offset_x; }
		inline float getOffsetY() const { return m_offset_y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_offset_x << ", " << m_offset_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_offset_x, m_offset_y;
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	public:
		
		inline float getButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int t_button) 
			: m_button(t_button) {}

		int m_button;
	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) 
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int t_button) 
			: MouseButtonEvent(t_button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}