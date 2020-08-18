#pragma once

#include "Event.h"

namespace Engine
{
	class ENGINE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int t_keycode) 
			: m_keycode(t_keycode) {}

		int m_keycode;
	};

	class ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int t_keycode, int t_repeat) 
			: KeyEvent(t_keycode), m_repeat(t_repeat) {}

		inline int getCount() const { return m_repeat; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeat << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeat;
	};

	class ENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int t_keycode) 
			: KeyEvent(t_keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class ENGINE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int t_keycode)
			: KeyEvent(t_keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}