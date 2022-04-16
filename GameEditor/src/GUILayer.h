#pragma once
#include <ProEngine.h>
#include "GUI/GUI.h"
#include "App.h"
#include "System/Sprite/Editor/SpriteMapEditor.h"

class GUILayer : public Pro::Layer
{
public:
	GUILayer(Pro::Registry* registry);

	~GUILayer() = default;

	virtual void OnAttach() override;
	virtual void OnUpdate(Pro::Timestep delta) override;
	virtual void OnEvent(Pro::Event & e) override;
	virtual void OnDetach() override;

	void SaveScene(std::string path);
	void LoadScene(std::string path);

	bool OnKeyPressed(Pro::KeyPressedEvent& e);


	void Inspector();
	void Properties();
	void ImageEditor();
	void ComponentSelector();

	std::string PickName();

public:
	Pro::PixelPerfectCamera m_cam;
	Pro::Renderer2D renderer;
	Pro::Registry* m_reg;

	Pro::Entity m_selectedEntity;

	Pro::SpriteLibrary m_spriteLibrary;
	SpriteMapEditor m_spriteMapEditor;
	
	bool m_terminalMode = false;
	bool m_componentSelectorOpen = false;
	bool m_isEntitySelected = false;
	int count = 0;


};
