#pragma once
#include "ProEngine.h"


class TestLayer : public Pro::Layer
{
public:
	TestLayer(Pro::Registry* reg) : m_scene(reg)
	{}

	virtual void OnAttach() override;
	virtual void OnUpdate(Pro::Timestep delta) override;
	virtual void OnEvent(Pro::Event& e) override;
	virtual void OnDetach() override;


private:
	Pro::Scene m_scene;
};

