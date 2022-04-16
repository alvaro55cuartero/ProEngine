#pragma once
#include "ProEngine.h"
#include "GUI/GUI.h"
#include "editor/Editor.h"
#include "System/Sprite/SpriteMap.h"

class SpriteMapEditor: public Editor
{
private:
	Pro::Vec2 ConvertToGridCoord(Pro::Vec2 position);
	void AddTile(Pro::Vec2 pos);

public:
	void OnUpdate() override;
	bool OnEvent(Pro::Event& e) override;
	void OnPropertiesGUI() override;
	void OnNewWidget() override;

private:
	uint32_t m_currentLayer;
	SpriteMap m_spriteMap;
	Pro::SpriteLibrary m_spriteLibrary;

	bool m_editMode = false;
	Pro::Vec2 m_grid = {32, 32};
};

