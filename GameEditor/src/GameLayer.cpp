#include "GameLayer.h"
//#include "System/TextureData.h"
#include "Scripts/PlayerController.h"

struct A
{

};

void GameLayer::OnAttach()
{
	PRO_PROFILE_FUNCTION();

	//TextureData text(256, 256, 4);
	//text.addData({10,10}, { 30,130,230,255 });
	//text.addData({ 11,10 }, { 30,130,230,255 });
	//text.addData({ 10,11 }, { 30,130,230,255 });
	//text.addData({11,11}, { 30,130,230,255 });
	//text.SavePNG("../Game/assets/img/png/img2.png");
	
	std::cout << Pro::Physics::TestYGrid({ 0, 64 }, 64, Pro::Physics::AABB({ 0, 32 }, { 32, 32})) << " false\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 63 }, 63, Pro::Physics::AABB({ 0, 32 }, { 32, 32 })) << " true\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 0 }, 32, Pro::Physics::AABB({ 0, 32 }, { 32, 32 })) << " false\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 0 }, 33, Pro::Physics::AABB({ 0, 32 }, { 32, 32 })) << " true\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 0 }, 64, Pro::Physics::AABB({ 0, 32 }, { 32, 32 })) << " true\n";


	std::cout << Pro::Physics::TestYGrid({ 0, 64 }, -32, Pro::Physics::AABB({ 0, 0 }, { 32, 32 })) << " false\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 64 }, -33, Pro::Physics::AABB({ 0, 0 }, { 32, 32 })) << " true\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 64 }, -90, Pro::Physics::AABB({ 0, 0 }, { 32, 32 })) << " true\n";
	std::cout << Pro::Physics::TestYGrid({ 0, 0 }, -32, Pro::Physics::AABB({ 0, 0 }, { 32, 32 })) << " true\n";
	std::cout << Pro::Physics::TestYGrid({ 0, -1 }, -33, Pro::Physics::AABB({ 0, 0 }, { 32, 32 })) << " false\n";


	

	TypeStorage type = {};
	type.AddClass<A>("a");
	type.CreateClass("a");
	
	
	m_scene.AddSystem(nullptr);


	if (m_scene.HasEntity("Player"))
	{
		Pro::Entity player = m_scene.GetEntity("Player");
		
		player.AddComponent<Pro::NativeScriptComponent>().Bind<PlayerController>();
	}
}


void GameLayer::OnUpdate(Pro::Timestep delta)
{
	PRO_PROFILE_FUNCTION();
	
	m_scene.OnUpdate(delta);
	

}

void GameLayer::OnEvent(Pro::Event& e)
{

}

void GameLayer::OnDetach()
{

}