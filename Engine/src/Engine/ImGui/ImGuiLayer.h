#pragma once

#include "Engine/Layer.h"

namespace Engine
{
	class ENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& p_event);

	private:
		bool onMouseButtonPressed(MouseButtonPressedEvent& p_event);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& p_event);
		bool onMouseMoved(MouseMovedEvent& p_event);
		bool onMouseScrolled(MouseScrolledEvent& p_event);
		
		bool onKeyPressed(KeyPressedEvent& p_event);
		bool onKeyReleased(KeyReleasedEvent& p_event);
		bool onKeyTyped(KeyTypedEvent& p_event);
		
		bool onWindowResize(WindowResizeEvent& p_event);
	private:
		float m_time = 0;
	};
}

