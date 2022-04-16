#pragma once

#include "ProEngine/Core/KeyCodes.h"
#include "ProEngine/Core/Input.h"

namespace Pro
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
	
	public:
		virtual void Update() override;

		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual Vec2 GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual float GetMouseDXImpl() override;
		virtual float GetMouseDYImpl() override;

		virtual int GetKey(int keycode) override;
		virtual void SetKey(int keycode, char value) override;

		virtual void AddCharToQueue(char c) override;


		int GetKeycode(int keycode);

		virtual void LockCursor(bool lock) override;



	private:
		void CreateKeyTables();

	private:
		short m_keycodes[512];
		
	};
}
