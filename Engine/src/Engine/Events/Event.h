#pragma once

#include "pch.h"

#include "Engine/Core.h"

namespace Engine
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication	= 0b00001,
		EventCategoryInput			= 0b00010,
		EventCategoryKeyboard		= 0b00100,
		EventCategoryMouse			= 0b01000,
		EventCategoryMouseButton	= 0b10000
	};

	#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::##type; }\
									virtual EventType getEventType() const override { return getStaticType(); }\
									virtual const char* getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class ENGINE_API Event 
	{
		friend class EventDispatcher;

	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) 
		{
			return getCategoryFlags() & category;
		}

	protected:
		bool m_handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFct = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& t_event) 
			: m_event(t_event) {}

		template<typename T>
		bool dispatch(EventFct<T> t_func) {
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.m_handled = t_func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& t_os, const Event& t_e) 
	{
		return t_os << t_e.toString();
	}
}
