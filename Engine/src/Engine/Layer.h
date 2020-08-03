#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& t_name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& t_event) {}

		inline const std::string& getName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}

