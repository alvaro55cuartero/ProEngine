#pragma once


class Editor
{
public:
	virtual void OnUpdate() = 0;
	virtual bool OnEvent(Pro::Event& e) = 0;
	virtual void OnPropertiesGUI() = 0;
	virtual void OnNewWidget() = 0;
};