#pragma once

#include "pch.h"

#include "Engine/Core.h"
#include "Engine/Log.h"
#include "Engine/Events/Event.h"


namespace Engine
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& t_title = "Engine", unsigned int t_width = 1280, unsigned int t_height = 720)
			: title(t_title), width(t_width), height(t_height) {}
	};

	class ENGINE_API Window 
	{
	public:
		using EventCallbackFct = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFct& t_callback) = 0;
		virtual void setVSync(bool t_enabled) = 0;
		virtual bool isVSyncEnabled() const = 0;

		static Window* create(const WindowProperties& t_properties = WindowProperties());
	};
}