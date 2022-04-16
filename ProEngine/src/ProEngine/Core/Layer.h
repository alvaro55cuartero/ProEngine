#pragma once
#include "ProEngine/Events/Event.h"
#include "Timestep.h"
#include <string>

namespace Pro 
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnUpdate(Timestep delta) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnDetach() {}

	private:
		std::string m_name;
	};
}

