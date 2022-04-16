#include "SpriteMapEditor.h"



Pro::Vec2 SpriteMapEditor::ConvertToGridCoord(Pro::Vec2 position)
{
	return position / m_grid;
}

void SpriteMapEditor::AddTile(Pro::Vec2 pos)
{
	
}

void SpriteMapEditor::OnUpdate() {}

bool SpriteMapEditor::OnEvent(Pro::Event& e)
{
	if (m_editMode)
	{
		if (Pro::MouseButtonPressedEvent* ev = dynamic_cast<Pro::MouseButtonPressedEvent*> (&e))
		{
			if (ev->GetMouseButton() == 0)
			{
				Pro::Vec2 position = ConvertToGridCoord({ ev->GetX(), ev->GetY() });
				AddTile(position);
				return true;
			}
		}
	}
	return false;
}

void SpriteMapEditor::OnPropertiesGUI() {}


void SpriteMapEditor::OnNewWidget()
{
	auto* input = Pro::Application::Get().GetWindow().GetInput();

	GUI::Begin("SpriteMap");
	if (GUI::Button("Edit"))
	{
		m_editMode = true;
	}

	if (GUI::Button("Stop"))
	{
		m_editMode = false;
	}


	GUI::InputInt("Layer", m_currentLayer);

	if ( GUI::Button("Add Layer")) {
		m_spriteMap.AddLayer(m_currentLayer);
	}

	GUI::End();
	
	
}