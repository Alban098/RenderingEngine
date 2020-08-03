#include "pch.h"
#include "Engine/LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack() 
	{
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* t_layer)
	{
		m_layerInsert = m_layers.emplace(m_layerInsert, t_layer);
	}

	void LayerStack::pushOverlay(Layer* t_overlay)
	{
		m_layers.emplace_back(t_overlay);
	}

	void LayerStack::popLayer(Layer* t_layer)
	{
		auto iterator = std::find(m_layers.begin(), m_layers.end(), t_layer);
		if (iterator != m_layers.end())
		{
			m_layers.erase(iterator);
			m_layerInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* t_overlay)
	{
		auto iterator = std::find(m_layers.begin(), m_layers.end(), t_overlay);
		if (iterator != m_layers.end())
			m_layers.erase(iterator);
	}
}