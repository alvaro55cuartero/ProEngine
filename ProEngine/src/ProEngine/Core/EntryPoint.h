#pragma once

#include "ProEngine/Core/Application.h"
#include "ProEngine/Debug/Instrumentor.h"

extern Pro::Application* Pro::CreateApplication();

int main() 
{
	PRO_PROFILE_BEGIN_SESSION("Startup", "ProEngineProfile-Startup.json");
	auto app = Pro::CreateApplication();
	PRO_PROFILE_END_SESSION();

	PRO_PROFILE_BEGIN_SESSION("Runtime", "ProEngineProfile-Runtime.json");
	app->Run();
	PRO_PROFILE_END_SESSION();

	PRO_PROFILE_BEGIN_SESSION("Shutdown", "ProEngineProfile-Shutdown.json");
	delete app;
	PRO_PROFILE_END_SESSION();


	return 0;
}