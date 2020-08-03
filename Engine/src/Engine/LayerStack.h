#pragma once

#include "Engine/Core.h"
#include "Engine/Layer.h"

#include <vector>

namespace Engine
{
	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void pushLayer(Layer* t_layer);
		void pushOverlay(Layer* t_overlay);
		void popLayer(Layer* t_layer);
		void popOverlay(Layer* t_overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		std::vector<Layer*>::iterator m_layerInsert;
	};
}

