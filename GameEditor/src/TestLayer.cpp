#include "TestLayer.h"

struct Component
{
public:
	Component(std::string tag) : tag(tag) {}

	std::string tag = "";
};


void TestLayer::OnAttach()
{
	m_scene.CreateEntity("");
}


void TestLayer::OnUpdate(Pro::Timestep delta)
{
	


}

void TestLayer::OnEvent(Pro::Event& e)
{

}

void TestLayer::OnDetach()
{

}