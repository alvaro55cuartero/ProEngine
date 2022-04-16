#include "Propch.h"
#include "WindowsInput.h"
#include "ProEngine/Core/Application.h"

#include <GLFW/glfw3.h>
#include <Platform/Windows/WindowsWindow.h>

namespace Pro 
{
	void WindowsInput::CreateKeyTables()
	{

		m_keycodes[0x00] = Pro::Button::Left;		//VK_LBUTTON: Left mouse button
		m_keycodes[0x01] = Pro::Button::Right;		//VK_RBUTTON: Right mouse button
		//m_keycodes[0x03] =						//VK_CANCEL:Control - break processing
		//m_keycodes[0x04] =						//VK_MBUTTON: Middle mouse button(three - button mouse)
		//m_keycodes[0x05] =						//VK_XBUTTON1: X1 mouse button
		//m_keycodes[0x06] =						//VK_XBUTTON2: X2 mouse button
		//m_keycodes[0x07] =						//-: Undefined
		m_keycodes[0x08] = Pro::Key::Backspace;		//VK_BACK: BACKSPACE key
		//m_keycodes[0x09] =						//VK_TAB: TAB key
		//m_keycodes[0x0A - 0x0B] =					//-:Reserved
		//m_keycodes[0x0C] =						//VK_CLEAR: CLEAR key
		m_keycodes[0x0D] = Pro::Key::Enter;			//VK_RETURN: ENTER key
		//m_keycodes[0x0E - 0F] =					//-: Undefined

		//m_keycodes[0x10] =						//VK_SHIFT: SHIFT key
		//m_keycodes[0x11] =						//VK_CONTROL: CTRL key
		//m_keycodes[0x12] =						//VK_MENU: ALT key
		//m_keycodes[0x13] =						//VK_PAUSE :PAUSE key
		//m_keycodes[0x14] =						//VK_CAPITAL :CAPS LOCK key

		//m_keycodes[0x15] =						//VK_KANA :IME Kana mode
		//m_keycodes[0x15] =						//VK_HANGUEL :IME Hanguel mode(maintained for compatibility; use VK_HANGUL)
		//m_keycodes[0x15] =						//VK_HANGUL :IME Hangul mode
		//m_keycodes[0x16] =						//VK_IME_ON :IME On
		//m_keycodes[0x17] =						//VK_JUNJA :IME Junja mode
		//m_keycodes[0x18] =						//VK_FINAL :IME final mode
		//m_keycodes[0x19] =						//VK_HANJA :IME Hanja mode
		//m_keycodes[0x19] =						//VK_KANJI :IME Kanji mode
		//m_keycodes[0x1A] =						//VK_IME_OFF :IME Off

		m_keycodes[0x1B] = Pro::Key::Escape;		//VK_ESCAPE :ESC key
		
		//m_keycodes[0x1C] =						//VK_CONVERT :IME convert
		//m_keycodes[0x1D] =						//VK_NONCONVERT :IME nonconvert
		//m_keycodes[0x1E] =						//VK_ACCEPT :IME accept
		//m_keycodes[0x1F] =						//VK_MODECHANGE :IME mode change request
		
		m_keycodes[0x20] = Pro::Key::Space;		//VK_SPACE: SPACEBAR

		//m_m_keycodes[0x21] =						//VK_PRIOR: PAGE UP key
		//m_m_keycodes[0x22] =						//VK_NEXT: PAGE DOWN key
		//m_m_keycodes[0x23] =						//VK_END: END key

		m_keycodes[0x24] = Pro::Key::Home;		//VK_HOME: HOME key

		m_keycodes[0x25] = Pro::Key::Left;		//VK_LEFT: LEFT ARROW key
		m_keycodes[0x26] = Pro::Key::Up;			//VK_UP: UP ARROW key
		m_keycodes[0x27] = Pro::Key::Right;		//VK_RIGHT: RIGHT ARROW key
		m_keycodes[0x28] = Pro::Key::Down;		//VK_DOWN: DOWN ARROW key

		//m_keycodes[0x29] =						//VK_SELECT: SELECT key
		//m_keycodes[0x2A] =						//VK_PRINT: PRINT key
		//m_keycodes[0x2B] =						//VK_EXECUTE: EXECUTE key
		//m_keycodes[0x2C] =						//VK_SNAPSHOT: PRINT SCREEN key
		//m_keycodes[0x2D] =						//VK_INSERT: INS key
		//m_keycodes[0x2E] =						//VK_DELETE: DEL key
		//m_keycodes[0x2F] =						//VK_HELP: HELP key


		m_keycodes[0x30] = Pro::Key::D0;			//0 key
		m_keycodes[0x31] = Pro::Key::D1;			//1 key
		m_keycodes[0x32] = Pro::Key::D2;			//2 key
		m_keycodes[0x33] = Pro::Key::D3;			//3 key
		m_keycodes[0x34] = Pro::Key::D4;			//4 key
		m_keycodes[0x35] = Pro::Key::D5;			//5 key
		m_keycodes[0x36] = Pro::Key::D6;			//6 key
		m_keycodes[0x37] = Pro::Key::D7;			//7 key
		m_keycodes[0x38] = Pro::Key::D8;			//8 key
		m_keycodes[0x39] = Pro::Key::D9;			//9 key
		

		//m_keycodes[0x3A - 40] = //- :Undefined


		m_keycodes[0x41] = Pro::Key::A;			//A key
		m_keycodes[0x42] = Pro::Key::B;			//B key
		m_keycodes[0x43] = Pro::Key::C;			//C key
		m_keycodes[0x44] = Pro::Key::D;			//D key
		m_keycodes[0x45] = Pro::Key::E;			//E key
		m_keycodes[0x46] = Pro::Key::F;			//F key
		m_keycodes[0x47] = Pro::Key::G;			//G key
		m_keycodes[0x48] = Pro::Key::H;			//H key
		m_keycodes[0x49] = Pro::Key::I;			//I key
		m_keycodes[0x4A] = Pro::Key::J;			//J key
		m_keycodes[0x4B] = Pro::Key::K;			//K key
		m_keycodes[0x4C] = Pro::Key::L;			//L key
		m_keycodes[0x4D] = Pro::Key::M;			//M key
		m_keycodes[0x4E] = Pro::Key::N;			//N key
		m_keycodes[0x4F] = Pro::Key::O;			//O key
		m_keycodes[0x50] = Pro::Key::P;			//P key
		m_keycodes[0x51] = Pro::Key::Q;			//Q key
		m_keycodes[0x52] = Pro::Key::R;			//R key
		m_keycodes[0x53] = Pro::Key::S;			//S key
		m_keycodes[0x54] = Pro::Key::T;			//T key
		m_keycodes[0x55] = Pro::Key::U;			//U key
		m_keycodes[0x56] = Pro::Key::V;			//V key
		m_keycodes[0x57] = Pro::Key::W;			//W key
		m_keycodes[0x58] = Pro::Key::X;			//X key
		m_keycodes[0x59] = Pro::Key::Y;			//Y key
		m_keycodes[0x5A] = Pro::Key::Z;			//Z key

		/*
		m_keycodes[0x5B] =								//VK_LWIN :Left Windows key(Natural keyboard)
		m_keycodes[0x5C] =								//VK_RWIN :Right Windows key(Natural keyboard)
		m_keycodes[0x5D] =								//VK_APPS :Applications key(Natural keyboard)
		m_keycodes[0x5E] =								//- :Reserved
		m_keycodes[0x5F] =								//VK_SLEEP :Computer Sleep key
		m_keycodes[0x60] =								//VK_NUMPAD0 :Numeric keypad 0 key
		m_keycodes[0x61] =								//VK_NUMPAD1 :Numeric keypad 1 key
		m_keycodes[0x62] =								//VK_NUMPAD2 :Numeric keypad 2 key
		m_keycodes[0x63] =								//VK_NUMPAD3 :Numeric keypad 3 key
		m_keycodes[0x64] =								//VK_NUMPAD4 :Numeric keypad 4 key
		m_keycodes[0x65] =								//VK_NUMPAD5 :Numeric keypad 5 key
		m_keycodes[0x66] =								//VK_NUMPAD6 :Numeric keypad 6 key
		m_keycodes[0x67] =								//VK_NUMPAD7 :Numeric keypad 7 key
		m_keycodes[0x68] =								//VK_NUMPAD8 :Numeric keypad 8 key
		m_keycodes[0x69] =								//VK_NUMPAD9 :Numeric keypad 9 key
		m_keycodes[0x6A] =								//VK_MULTIPLY :Multiply key
		m_keycodes[0x6B] =								//VK_ADD :Add key
		m_keycodes[0x6C] =								//VK_SEPARATOR :Separator key
		m_keycodes[0x6D] =								//VK_SUBTRACT :Subtract key
		m_keycodes[0x6E] =								//VK_DECIMAL :Decimal key
		m_keycodes[0x6F] =								//VK_DIVIDE :Divide key
		*/


		m_keycodes[0x70] = Pro::Key::F1;					//VK_F1 :F1 key
		m_keycodes[0x71] = Pro::Key::F2;					//VK_F2 :F2 key
		m_keycodes[0x72] = Pro::Key::F3;					//VK_F3 :F3 key
		m_keycodes[0x73] = Pro::Key::F4;					//VK_F4 :F4 key
		m_keycodes[0x74] = Pro::Key::F5;					//VK_F5 :F5 key
		m_keycodes[0x75] = Pro::Key::F6;					//VK_F6 :F6 key
		m_keycodes[0x76] = Pro::Key::F7;					//VK_F7 :F7 key
		m_keycodes[0x77] = Pro::Key::F8;					//VK_F8 :F8 key
		m_keycodes[0x78] = Pro::Key::F9;					//VK_F9 :F9 key
		m_keycodes[0x79] = Pro::Key::F10;					//VK_F10 :F10 key
		m_keycodes[0x7A] = Pro::Key::F11;					//VK_F11 :F11 key
		m_keycodes[0x7B] = Pro::Key::F12;					//VK_F12 :F12 key
		m_keycodes[0x7C] = Pro::Key::F13;					//VK_F13 :F13 key
		m_keycodes[0x7D] = Pro::Key::F14;					//VK_F14 :F14 key
		m_keycodes[0x7E] = Pro::Key::F15;					//VK_F15 :F15 key
		m_keycodes[0x7F] = Pro::Key::F16;					//VK_F16 :F16 key
		m_keycodes[0x80] = Pro::Key::F17;					//VK_F17 :F17 key
		m_keycodes[0x81] = Pro::Key::F18;					//VK_F18 :F18 key
		m_keycodes[0x82] = Pro::Key::F19;					//VK_F19 :F19 key
		m_keycodes[0x83] = Pro::Key::F20;					//VK_F20 :F20 key
		m_keycodes[0x84] = Pro::Key::F21;					//VK_F21 :F21 key
		m_keycodes[0x85] = Pro::Key::F22;					//VK_F22 :F22 key
		m_keycodes[0x86] = Pro::Key::F23;					//VK_F23 :F23 key
		m_keycodes[0x87] = Pro::Key::F24;					//VK_F24 :F24 key


		//m_keycodes[0x88 - 8F] =							//- :Unassigned
		//m_keycodes[0x90] =								//VK_NUMLOCK :NUM LOCK key
		//m_keycodes[0x91] =								//VK_SCROLL :SCROLL LOCK key
		//m_keycodes[0x92 - 96] =							//OEM specific
		//m_keycodes[0x97 - 9F] =							//- :Unassigned
		m_keycodes[0xA0] = Pro::Key::LeftShift;			//VK_LSHIFT :Left SHIFT key
		m_keycodes[0xA1] = Pro::Key::RightShift;			//VK_RSHIFT :Right SHIFT key
		m_keycodes[0xA2] = Pro::Key::LeftControl;			//VK_LCONTROL :Left CONTROL key
		m_keycodes[0xA3] = Pro::Key::RightControl;		//VK_RCONTROL :Right CONTROL key
		//m_keycodes[0xA4] = 								//VK_LMENU :Left MENU key
		//m_keycodes[0xA5] =								//VK_RMENU :Right MENU key
		//m_keycodes[0xA6] =								//VK_BROWSER_BACK :Browser Back key
		//m_keycodes[0xA7] =								//VK_BROWSER_FORWARD :Browser Forward key
		//m_keycodes[0xA8] =								//VK_BROWSER_REFRESH :Browser Refresh key
		//m_keycodes[0xA9] =								//VK_BROWSER_STOP :Browser Stop key
		//m_keycodes[0xAA] =								//VK_BROWSER_SEARCH :Browser Search key
		//m_keycodes[0xAB] =								//VK_BROWSER_FAVORITES :Browser Favorites key
		//m_keycodes[0xAC] =								//VK_BROWSER_HOME :Browser Start and Home key
		//m_keycodes[0xAD] =								//VK_VOLUME_MUTE :Volume Mute key
		//m_keycodes[0xAE] =								//VK_VOLUME_DOWN :Volume Down key
		//m_keycodes[0xAF] =								//VK_VOLUME_UP :Volume Up key
		//m_keycodes[0xB0] =								//VK_MEDIA_NEXT_TRACK :Next Track key
		//m_keycodes[0xB1] =								//VK_MEDIA_PREV_TRACK :Previous Track key
		//m_keycodes[0xB2] =								//VK_MEDIA_STOP :Stop Media key
		//m_keycodes[0xB3] =								//VK_MEDIA_PLAY_PAUSE :Play / Pause Media key
		//m_keycodes[0xB4] =								//VK_LAUNCH_MAIL :Start Mail key
		//m_keycodes[0xB5] =								//VK_LAUNCH_MEDIA_SELECT :Select Media key
		//m_keycodes[0xB6] =								//VK_LAUNCH_APP1 :Start Application 1 key
		//m_keycodes[0xB7] =								//VK_LAUNCH_APP2 :Start Application 2 key
		//m_keycodes[0xB8 - B9] =							//- :Reserved
		//m_keycodes[0xBA] =								//VK_OEM_1 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the ';:' key
		//m_keycodes[0xBB] =								//VK_OEM_PLUS :For any country / region, the '+' key
		//m_keycodes[0xBC] =								//VK_OEM_COMMA :For any country / region, the ',' key
		//m_keycodes[0xBD] =								//VK_OEM_MINUS :For any country / region, the '-' key
		//m_keycodes[0xBE] =								//VK_OEM_PERIOD :For any country / region, the '.' key
		//m_keycodes[0xBF] =								//VK_OEM_2 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '/?' key
		//m_keycodes[0xC0] =								//VK_OEM_3 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '`~' key
		//m_keycodes[0xC1 - D7] =							//- :Reserved
		//m_keycodes[0xD8 - DA] =							//- :Unassigned
		//m_keycodes[0xDB] =								//VK_OEM_4 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '[{' key
		//m_keycodes[0xDC] =								//VK_OEM_5 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the '\|' key
		//m_keycodes[0xDD] =								//VK_OEM_6 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the ']}' key
		//m_keycodes[0xDE] =								//VK_OEM_7 :Used for miscellaneous characters; it can vary by keyboard.For the US standard keyboard, the 'single-quote/double-quote' key
		//m_keycodes[0xDF] =								//VK_OEM_8 :Used for miscellaneous characters; it can vary by keyboard.
		//m_keycodes[0xE0] =								//- :Reserved
		//m_keycodes[0xE1] =								//OEM specific
		//m_keycodes[0xE2] =								//VK_OEM_102 :Either the angle bracket key or the backslash key on the RT 102 - key keyboard
		//m_keycodes[0xE3 - 0xE4] =						//OEM specific
		//m_keycodes[0xE5] =								//VK_PROCESSKEY :IME PROCESS key
		//m_keycodes[0xE6] =								//OEM specific
		//m_keycodes[0xE7] =								//VK_PACKET :Used to pass Unicode characters as if they were keystrokes.The VK_PACKET key is the low word of a 32 - bit Virtual Key value used for non - keyboard input methods.For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
		//m_keycodes[0xE8] =								//- :Unassigned
		//m_keycodes[0xE9 - 0xF5] =						//OEM specific
		//m_keycodes[0xF6] =								//VK_ATTN :Attn key
		//m_keycodes[0xF7] =								//VK_CRSEL :CrSel key
		//m_keycodes[0xF8] =								//VK_EXSEL :ExSel key
		//m_keycodes[0xF9] =								//VK_EREOF :Erase EOF key
		//m_keycodes[0xFA] =								//VK_PLAY :Play key
		//m_keycodes[0xFB] =								//VK_ZOOM :Zoom key
		//m_keycodes[0xFC] =								//VK_NONAME :Reserved
		//m_keycodes[0xFD] =								//VK_PA1 :PA1 key
		//m_keycodes[0xFE] =								//VK_OEM_CLEAR: Clear key

	}


	WindowsInput::WindowsInput()
	{
		m_lock = false;
		memset(m_keys, 0, sizeof(m_keys));
		CreateKeyTables();
	}

	void WindowsInput::Update()
	{ 
		auto window = static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow());

		m_mousePos = GetMousePositionImpl();
		
		RECT rect;
		GetWindowRect(window, &rect);
		
		Vec2 center = { (float)(int)((rect.left + rect.right) / 2), (float)(int)((rect.top + rect.bottom) / 2) };

		
		if (!m_lock)
		{
			m_deltaMousePos = m_mousePos - m_lastMousePos;
			m_lastMousePos = m_mousePos;
		}
		else 
		{
			POINT a;
			GetCursorPos(&a);
			m_mousePos = { (float)a.x, (float)a.y };
			m_deltaMousePos = m_mousePos - center;
			
			SetCursorPos(center.x, center.y);

		}

		if (IsMouseButtonPressedImpl(Pro::Button::Left) == PRO_PRESS)
		{
			m_keys[Pro::Button::Left] = PRO_REPEAT;
		}

		//std::string s = std::string(m_charQueue.begin(), m_charQueue.end());
		//std::cout << s << std::endl;

		m_charQueue.clear();
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return (int)GetKey(keycode);
	}


	int WindowsInput::GetKeycode(int keycode) {
		return m_keycodes[keycode];
	}

	void WindowsInput::LockCursor(bool lock)
	{
		//glfwGetCursorPos();

		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//auto pos = Application::Get().GetWindow().GetMousePos();
		if (lock) {
			ShowCursor(false);
			m_lock = true;
			m_virtualMousePos = m_mousePos;
		}
		else
		{
			ShowCursor(true);
			m_lock = false;
		}

		//_glfwPlatformGetCursorPos(window, &_glfw.win32.restoreCursorPosX, &_glfw.win32.restoreCursorPosY);
		//updateCursorImage(window);
		//_glfwCenterCursorInContentArea(window);
		//updateClipRect(window);
	
	}

	void WindowsInput::AddCharToQueue(char c)
	{
		m_charQueue.push_back(c);
	}

	int WindowsInput::GetKey(int keycode) {
		return m_keys[keycode];
	}

	void WindowsInput::SetKey(int keycode, char value) {
		m_keys[keycode] = value;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto state = GetKey(button);
		return state == PRO_PRESS;
	}

	Vec2 WindowsInput::GetMousePositionImpl()
	{
		return Application::Get().GetWindow().GetMousePos();
	}

	float WindowsInput::GetMouseXImpl()
	{
		return m_mousePos.x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return m_mousePos.y;
	}

	float WindowsInput::GetMouseDXImpl()
	{
		return m_deltaMousePos.x;
	}

	float WindowsInput::GetMouseDYImpl()
	{
		return m_deltaMousePos.y;
	}

}
