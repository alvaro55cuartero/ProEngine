#include "GUILayer.h"


GUILayer::GUILayer(Pro::Registry* registry)
	: m_reg(registry), m_cam(Pro::PixelPerfectCamera(1280, 720))
{
	PRO_PROFILE_FUNCTION();


}


void GUILayer::OnAttach()
{
	PRO_PROFILE_FUNCTION();

	m_spriteMapEditor = SpriteMapEditor();

	std::string data = Pro::File::Load("Assets/Json/textures.json");
	nlohmann::json json = nlohmann::json::parse(data);
	m_spriteLibrary.Deserialize(json);
	

	
	auto save = m_spriteLibrary.Serialize();
	Pro::File::Save(save.dump(4), "Assets/Json/textures.json");
	

	GUI::Init();
	GUI::SetFontTexture(m_spriteLibrary);
}

void GUILayer::OnUpdate(Pro::Timestep delta)
{
	PRO_PROFILE_FUNCTION();

	{
		PRO_PROFILE_SCOPE("Renderer Draw");


		if (m_terminalMode)
		{
			GUI::BeginMainToolbar();
			GUI::EndMainToolbar();

			Inspector();
			Properties();
			ImageEditor();
			m_spriteMapEditor.OnNewWidget();
			GUI::Render(m_cam);
		}
	}
}

void GUILayer::SaveScene(std::string path)
{
	nlohmann::json j;


	for (uint32_t i = 0; i < m_reg->GetCount(); i++)
	{

		if (m_reg->Has<Pro::TagComponent>(i))
		{
			Pro::TagComponent& tag = m_reg->Get<Pro::TagComponent>(i);
			j[i]["Tag"] = tag.Serialize();
		}

		if (m_reg->Has<Pro::CameraComponent>(i))
		{
			Pro::CameraComponent& cam = m_reg->Get<Pro::CameraComponent>(i);
			j[i]["Camera"] = cam.Serialize();
		}

		if (m_reg->Has<Pro::TransformComponent>(i))
		{
			Pro::TransformComponent& transform = m_reg->Get<Pro::TransformComponent>(i);
			j[i]["Transform"] = transform.Serialize();
		}

		if (m_reg->Has<Pro::SpriteComponent>(i))
		{
			Pro::SpriteComponent& sprite = m_reg->Get<Pro::SpriteComponent>(i);
			j[i]["Sprite"] = sprite.Serialize();
		}
	}


	Pro::File::Save(j.dump(4), path);
}

void GUILayer::LoadScene(std::string path)
{
	std::string text = Pro::File::Load(path);

	nlohmann::json json = nlohmann::json::parse(text);

	for (auto data : json)
	{
		Pro::Entity entity = m_reg->CreateEntity();

		if (data.contains("Tag"))
		{
			m_reg->Emplace<Pro::TagComponent>(entity).Deserialize(data["Tag"]);
		}

		if (data.contains("Transform"))
		{
			m_reg->Emplace<Pro::TransformComponent>(entity).Deserialize(data["Transform"]);
		}

		if (data.contains("Sprite"))
		{
			m_reg->Emplace<Pro::SpriteComponent>(entity).Deserialize(data["Sprite"]);
		}

		if (data.contains("Camera"))
		{
			m_reg->Emplace<Pro::CameraComponent>(entity).Deserialize(data["Camera"]);
		}
	}
}


void GUILayer::OnEvent(Pro::Event& e)
{
	PRO_PROFILE_FUNCTION();

	if(GUI::OnEvent(e)) return;

	if (m_spriteMapEditor.OnEvent(e)) return;

	Pro::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Pro::KeyPressedEvent>(PRO_BIND_EVENT_FN(GUILayer::OnKeyPressed));

}

bool GUILayer::OnKeyPressed(Pro::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == Pro::Key::T)
	{
		m_terminalMode = !m_terminalMode;
	}

	return false;
}


void GUILayer::OnDetach()
{
	PRO_PROFILE_FUNCTION();
	GUI::Finish();
}


void GUILayer::Inspector()
{
	GUI::Begin("Inspector");

	if (GUI::Button("Save"))
	{
		SaveScene("../Game/assets/Json/entities.json");
	}

	if (GUI::Button("Load"))
	{
		LoadScene("../Game/assets/Json/entities.json");
	}

	if (GUI::Button("Create"))
	{
		Pro::Entity entt = m_reg->CreateEntity();
		Pro::TagComponent tag = m_reg->Emplace<Pro::TagComponent>(entt, PickName());

	}

	for (int i = 0; i < m_reg->GetCount(); i++)
	{
		Pro::TagComponent tag = m_reg->Get<Pro::TagComponent>(i);
		if (GUI::Button(tag.Tag))
		{
			m_isEntitySelected = true;
			m_selectedEntity = Pro::Entity(i, m_reg);

		}
	}

	GUI::End();
}

void GUILayer::Properties()
{
	
	GUI::Begin("Properties");
	if (m_isEntitySelected)
	{

		if (m_reg->Has<Pro::TagComponent>(m_selectedEntity)) {
			auto tag = m_reg->Get<Pro::TagComponent>(m_selectedEntity);
			GUI::Text("Name: " + tag.Tag);
		}



		if (m_reg->Has<Pro::TransformComponent>(m_selectedEntity)) {
			auto& transform = m_reg->Get<Pro::TransformComponent>(m_selectedEntity);
			GUI::Space();
			GUI::Text("Transform Component");
			//GUI::Text("Position: " + std::to_string((int)transform.Translation.x) + " " + std::to_string((int)transform.Translation.y) + " " + std::to_string((int)transform.Translation.y));
			GUI::InputVec3("Position", transform.Translation.x, transform.Translation.y, transform.Translation.z);
			GUI::InputVec3("Scale", transform.Scale.x, transform.Scale.y, transform.Scale.z);
		}

		if (m_reg->Has<Pro::SpriteComponent>(m_selectedEntity)) {
			auto& sprite = m_reg->Get<Pro::SpriteComponent>(m_selectedEntity);
			GUI::Space();
			GUI::Text("Sprite Component");
			GUI::InputColor("Color", sprite.Color.x, sprite.Color.y, sprite.Color.z, sprite.Color.w);
			GUI::InputText("Sprite", sprite.Sprite);
		}
	
		GUI::Space();

		if (GUI::Button("Component"))
		{
			m_componentSelectorOpen = true;
		}

		if (m_componentSelectorOpen)
		{
			ComponentSelector();
		}
	}
	GUI::End();
}

void GUILayer::ImageEditor()
{
	GUI::Window* window = GUI::Begin("ImageEditor");	
	Pro::Vec2 size = window->GetSize();
	GUI::Image(m_spriteLibrary.Get("COLUMNA"), size);
	GUI::Image(m_spriteLibrary.Get("COLUMNA"), size);
	GUI::End();
}

void GUILayer::ComponentSelector()
{
	if (GUI::Button("Transform"))
	{
		m_reg->Emplace<Pro::TransformComponent>(m_selectedEntity);
		m_componentSelectorOpen = false;
	}

	if (GUI::Button("Sprite"))
	{
		m_reg->Emplace<Pro::SpriteComponent>(m_selectedEntity);
		m_componentSelectorOpen = false;
	}
}

std::string GUILayer::PickName()
{
	return  "Entity" + std::to_string(m_reg->GetCount());
}