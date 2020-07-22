#pragma once

#include "Event.h"

namespace Engine
{
	class ENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int t_width, unsigned int t_height) 
			: m_width(t_width), m_height(t_height) {}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_width, m_height;
	};

	class ENGINE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppTickEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppUpdateEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppRenderEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}