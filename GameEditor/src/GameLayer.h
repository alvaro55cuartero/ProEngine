#pragma once
#include "ProEngine.h"
#include "System/Physics.h"

class GameLayer : public Pro::Layer
{
public:
	GameLayer(Pro::Registry* reg)
		: m_scene(reg)
	{}

	virtual void OnAttach() override;
	virtual void OnUpdate(Pro::Timestep delta) override;
	virtual void OnEvent(Pro::Event& e) override;
	virtual void OnDetach() override;


private:

	Pro::Scene m_scene;
};

