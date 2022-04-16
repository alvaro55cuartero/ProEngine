#include "App.h"
#include "ProEngine/Core/EntryPoint.h"
#include "GameLayer.h"
#include "TestLayer.h"
#include "GUILayer.h"

App::App()
{
	reg = new Pro::Registry();

	PushLayer(new GameLayer(reg));
	//PushLayer(new TestLayer(reg));
	//PushLayer(new GUILayer(/*ECS*/));
}

App::~App()
{

}

Pro::Application* Pro::CreateApplication()
{
	return new App();
}


