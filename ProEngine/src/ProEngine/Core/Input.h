#pragma once
#include <utility>
#include "ProEngine/Math/Vec2.h"
#include <vector>

#define PRO_RELEASE 0
#define PRO_PRESS 1
#define PRO_REPEAT 2

#define PRO_MOUSE_BUTTON_1         0
#define PRO_MOUSE_BUTTON_2         1
#define PRO_MOUSE_BUTTON_3         2
#define PRO_MOUSE_BUTTON_4         3
#define PRO_MOUSE_BUTTON_5         4
#define PRO_MOUSE_BUTTON_6         5
#define PRO_MOUSE_BUTTON_7         6
#define PRO_MOUSE_BUTTON_8         7
#define PRO_MOUSE_BUTTON_LAST      PRO_MOUSE_BUTTON_8
#define PRO_MOUSE_BUTTON_LEFT      PRO_MOUSE_BUTTON_1
#define PRO_MOUSE_BUTTON_RIGHT     PRO_MOUSE_BUTTON_2
#define PRO_MOUSE_BUTTON_MIDDLE    PRO_MOUSE_BUTTON_3


namespace Pro
{
	class Input
	{
	public:
		//bool IsKeyPressed(int keycode) { return s_instance->IsKeyPressedImpl(keycode); }

		//bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
		//std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
		//float GetMouseX() { return s_instance->GetMouseXImpl(); }
		//float GetMouseY() { return s_instance->GetMouseYImpl(); }

	public:
		virtual void Update() = 0;

		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual Vec2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual float GetMouseDXImpl() = 0;
		virtual float GetMouseDYImpl() = 0;

		virtual int GetKey(int keycode) = 0;
		virtual void SetKey(int keycode, char value) = 0;

		virtual void AddCharToQueue(char c) = 0;
		
		std::vector<char> GetCharQueue() { return m_charQueue; }

		virtual void LockCursor(bool lock) = 0;

	public:
		static Input* Create();

	protected:
		std::vector<char> m_charQueue;
		char m_keys[512];
		Vec2 m_mousePos;
		Vec2 m_deltaMousePos;
		Vec2 m_lastMousePos;
		Vec2 m_virtualMousePos;
		bool m_lock;
	};
}