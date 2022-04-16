#include "Propch.h"
#include "LayerStack.h"

namespace Pro
{

	LayerStack::~LayerStack() 
	{
		for (Layer* layer: m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();

	}
	
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
	}

}