#pragma once
#include "ProEngine.h"
#include "Window.h"
#include <string>
#include <deque>

namespace GUI
{
	struct DefaultValues
	{
		Pro::Vec4 fontColor = { 1, 1, 1, 1 };
		int fontSize = 8;

		Pro::Vec4 windowBorderColor = { 42.0f / 255.0f, 69.0f / 255.0f, 75.0f / 255.0f, 1.0f };
		Pro::Vec4 windowBackgroundColor = { 23.0f / 255.0f, 42.0f / 255.0f, 50.0f / 255.0f, 1.0f };
		Pro::Vec4 windowMainToolbarColor = { 23.0f / 255.0f, 42.0f / 255.0f, 50.0f / 255.0f, 1.0f };

		float windowBorderSize = 1;

		Pro::Vec4 buttonColor = { 42.0f / 255.0f, 69.0f / 255.0f, 75.0f/ 255.0f, 1.0f };
		Pro::Vec4 buttonHoverColor = { 71.0f / 255.0f, 98.0f / 255.0f, 104.0f / 255.0f, 1.0f };
	};


	struct IDStack
	{
	public:
		uint32_t PushID(std::string text)
		{
			uint32_t last = 0;
			if (m_ids.size() != 0) last = m_ids.back();

			uint32_t id = Pro::CRC32::Hash(text, last);
			m_ids.push_back(id);
			return id;
		}
		
		uint32_t PopID()
		{
			uint32_t last = m_ids.back();
			m_ids.pop_back();
			return last;
		}

		uint32_t GetCurrentId()
		{
			return m_ids.back();
		}

		void Reset()
		{
			m_ids.clear();
		}
	private:
		std::vector<uint32_t> m_ids;
	};




	class GUI
	{

	private:
		GUI() {};

		Window* NewWindow(std::string name)
		{
			if (!IsNameFree(name)) name = "Window" + m_windows.size();

			Window* window;
			if (data.contains(name)) 
			{
				Pro::Vec2 position = { data[name]["Position"]["x"].get<float>(), data[name]["Position"]["y"].get<float>() };
				Pro::Vec2 scale = { data[name]["Scale"]["x"].get<float>(), data[name]["Scale"]["y"].get<float>() };

				window = new Window(name, position, scale);
			}
			else
			{
				window = new Window(name, { 0,0 }, { 200, 720 });
			}

			m_windows.push_back(window);
			return window;
		}

		bool IsNameFree(std::string name) 
		{
			for (auto window: m_windows) 
			{
				if (name == window->GetName())
				{
					return false;
				}

			}
			return true;
		}

		Window* GetWindow(std::string name)
		{
			for (auto window: m_windows)
			{
				if (window->GetName() == name)
				{
					return window;
				}
			}
			return nullptr;
		}

		void RenderWindow(Window* window)
		{
			Pro::Vec2 position = window->GetPosition();
			Pro::Vec2 size = window->GetSize();
			std::string name = window->GetName();

			

			m_renderer.AddSquare(position, size, def.windowBorderColor);
			m_renderer.AddSquare(position + Pro::Vec2(def.windowBorderSize, def.windowBorderSize), size - Pro::Vec2(def.windowBorderSize, def.windowBorderSize + 8) * 2, def.windowBackgroundColor);
			RenderText(name, position + Pro::Vec2(10, size.y - 8 - 4));
			RenderText("X", position + Pro::Vec2(size.x - 10 - 8, size.y - 8 - 4));
		}

		void RenderText(std::string name, Pro::Vec2 position)
		{
			m_renderer.AddText(name, position, def.fontColor, def.fontSize, m_font);
		}

		Pro::Vec2 InputBox(std::string label, float& f, Pro::Vec2 position, uint32_t minLength = 0)
		{
			PushID(label);

			// Value of f has change between frames
			if (f != m_currentInputFloat)
			{ 
				m_currentInputFloat = f;
			}
			
		
			// Getting current text
			std::string text;
			if (IsFocus() && m_currentInputText.has_value()) {
				text = m_currentInputText.value();
			}
			else
			{
				text = std::to_string(f);
			}

			// Calculate the length of the box
			
			size_t textLength = text.size() * def.fontSize;
			Pro::Vec2 size((float)textLength, (float)def.fontSize);

			
			if (TryFocus(position, size))
			{
				m_currentInputText = std::to_string(f);
			}

			if (IsFocus())
			{
				for (char c : input->GetCharQueue())
				{
					std::cout << (int)c << "\n";
					if (c == 8)
					{
						if (m_currentInputText.value().size() > 0)
							m_currentInputText.value().pop_back();
					}
					else if(c == 13)
					{
						f = std::stof(m_currentInputText.value());
						ReleaseFocus();
						m_currentInputText.reset();
					}
					else
					{
						m_currentInputText.value().push_back(c);
					}
				}
			}

			textLength = text.size() * def.fontSize;
			size = Pro::Vec2((float)max(textLength, minLength), (float)def.fontSize);
			
			m_renderer.AddSquare(position, size, def.windowBorderColor);
			RenderText(text, position);
			
			return size;
		}

		Pro::Vec2 InputBox(std::string label, uint32_t& f, Pro::Vec2 position, uint32_t minLength = 0)
		{
			PushID(label);

			// Value of f has change between frames
			if (f != m_currentInputInt)
			{
				m_currentInputInt = f;
			}


			// Getting current text
			std::string text;
			if (IsFocus() && m_currentInputText.has_value()) {
				text = m_currentInputText.value();
			}
			else
			{
				text = std::to_string(f);
			}

			// Calculate the length of the box

			size_t textLength = text.size() * def.fontSize;
			Pro::Vec2 size((float)textLength, (float)def.fontSize);


			if (TryFocus(position, size))
			{
				m_currentInputText = std::to_string(f);
			}

			if (IsFocus())
			{
				for (char c : input->GetCharQueue())
				{
					std::cout << (int)c << "\n";
					if (c == 8)
					{
						if (m_currentInputText.value().size() > 0)
							m_currentInputText.value().pop_back();
					}
					else if (c == 13)
					{
						f = std::stoi(m_currentInputText.value());
						ReleaseFocus();
						m_currentInputText.reset();
					}
					else
					{
						m_currentInputText.value().push_back(c);
					}
				}
			}

			textLength = text.size() * def.fontSize;
			size = Pro::Vec2((float)max(textLength, minLength), (float)def.fontSize);

			m_renderer.AddSquare(position, size, def.windowBorderColor);
			RenderText(text, position);

			return size;
		}


		void LoadData()
		{
			std::string text = Pro::File::Load("./Assets/GUI/data.json");
			if (text == "") text = "{}";
			data = nlohmann::json::parse(text);
		}

		void SaveData()
		{
			Pro::File::Save(data.dump(4), "./Assets/GUI/data.json");
			
		}


		//Grab API

		bool TryGrab(Pro::Vec2 position, Pro::Vec2 size)
		{
			if (!IsGrabbing() && input->IsMouseButtonPressedImpl(0) && Pro::Math::isInside(position, size, input->GetMousePositionImpl()))
			{
				SetGrabbing();
				return true;
			}
			return false;
		}

		bool IsGrabbing()
		{
			return m_currentWindow == m_currentWindowGrabbed;
		}

		void SetGrabbing()
		{
			m_currentWindow = m_currentWindowGrabbed;
		}

		void ReleaseGrab()
		{
			m_currentWindowGrabbed = nullptr;
		}
		
		
		//Focus API
		
		//return true on first frame focus
		bool TryFocus(Pro::Vec2 position, Pro::Vec2 size)
		{
			if (!IsFocus() && input->IsMouseButtonPressedImpl(0) && Pro::Math::isInside(position, size, input->GetMousePositionImpl()))
			{
				SetFocus();
				return true;
			}
			return false;
		}

		void ReleaseFocus()
		{
			m_focusWidgetId = -1;
		}

		bool IsFocus()
		{
			return GetCurrentID() == m_focusWidgetId;
		}

		void SetFocus()
		{
			m_focusWidgetId = m_ids.GetCurrentId();
		}

		//IDStack API

		uint32_t PushID(std::string text)
		{
			return m_ids.PushID(text);
		}

		uint32_t PopID()
		{
			return m_ids.PopID();
		}

		uint32_t GetCurrentID()
		{
			return m_ids.GetCurrentId();
		}


	public:
		GUI(const GUI&) = delete;
		void operator=(const GUI&) = delete;

		void Init()
		{
			input = Pro::Application::Get().GetWindow().GetInput();
			m_renderer = Pro::Renderer2D();

			m_renderer.Init();
			LoadData();

			
		}

		void SetFontTexture(const Pro::SpriteLibrary& texture)
		{
			m_font = texture;
		}

		Window* Begin(std::string name)
		{
			PushID(name);

			m_currentWindow = GetWindow(name);
			if (!m_currentWindow) {

				m_currentWindow = NewWindow(name);
			}
			m_currentWindow->Reset();
			
			Pro::Vec2 position = m_currentWindow->GetPosition() + Pro::Vec2(0, m_currentWindow->GetSize().y - 16);
			Pro::Vec2 size = { m_currentWindow->GetSize().x, 16.0f};
			if (TryGrab(position, size))
			{
				std::cout << "a\n";
			}
				
			if (IsGrabbing() && !input->IsMouseButtonPressedImpl(0))
			{
				ReleaseGrab();
			}
			if (IsGrabbing())
			{
				m_currentWindow->AddPosition(Pro::Vec2(input->GetMouseDXImpl(), input->GetMouseDYImpl()));
			}

			if(m_currentWindow->IsVisible())
				RenderWindow(m_currentWindow);

			
			
			return GetCurrentWindow();
			//m_renderer.AddSquare(position, size, {0.5,0.4,0.2,1});
		}

		void End()
		{
			m_currentWindow->SetVisible(false);
			data[m_currentWindow->GetName()]["Position"]["x"] = m_currentWindow->GetPosition().x;
			data[m_currentWindow->GetName()]["Position"]["y"] = m_currentWindow->GetPosition().y;

			data[m_currentWindow->GetName()]["Scale"]["x"] = m_currentWindow->GetSize().x;
			data[m_currentWindow->GetName()]["Scale"]["y"] = m_currentWindow->GetSize().y;

			m_currentWindow = nullptr;
			PopID();
		}

		void BeginMainToolbar()
		{
			PushID("MainToolbar");
			float height = (float)Pro::Application::Get().GetWindow().GetHeight();
			float width = (float)Pro::Application::Get().GetWindow().GetWidth();
			
			m_renderer.AddSquare(Pro::Vec2(0, height - 20), Pro::Vec2(width,20), def.windowMainToolbarColor);
		}

		void EndMainToolbar()
		{
			PopID();
		}

		//Widgets

		void Text(const std::string& text)
		{
			Pro::Vec2 position = m_currentWindow->GetCursor();

			RenderText(text, position);

			m_currentWindow->SetCursor({0, -16});
		}

		bool Button(const std::string& text)
		{
			PushID(text);

			size_t textLength = text.size() * def.fontSize;
			
			Pro::Vec2 position = m_currentWindow->GetCursor();
			Pro::Vec2 size(textLength + 20.0f, def.fontSize + 2.0f);

			bool hovered = Pro::Math::isInside(position, size, input->GetMousePositionImpl());

			if (hovered) {
				m_renderer.AddSquare(position, size, def.buttonHoverColor);
			}
			else
			{
				m_renderer.AddSquare(position, size, def.buttonColor);
			}

			RenderText(text, position + Pro::Vec2(10, 1));


			m_currentWindow->SetCursor({ 0, -16 });

			return  input->IsMouseButtonPressedImpl(0) == PRO_PRESS && hovered;

			PopID();
		}

		void Space(int i = 1)
		{
			m_currentWindow->SetCursor({ 0, (float) (- 16 * i)});
		}

		void InputText(std::string label, std::string& buffer)
		{
			PushID(label);
				
			size_t bufferLength = buffer.size() * def.fontSize;

			Pro::Vec2 position = m_currentWindow->GetCursor();
			Pro::Vec2 size = Pro::Vec2((float)max(bufferLength, 100), (float)def.fontSize);
			auto input = Pro::Application::Get().GetWindow().GetInput();

			size_t labelLength = label.size() * def.fontSize;

			RenderText(label, m_currentWindow->GetCursor());

		
			
			if (IsFocus())
			{

				for (char c : input->GetCharQueue())
				{
					if (c == 8)
					{
						if (buffer.size() > 0)
							buffer.pop_back();
					}
					else
					{
						buffer.push_back(c);
					}
				}
			}


			m_currentWindow->SetCursor({ (float)labelLength, 0 });
			position = m_currentWindow->GetCursor();

			if (!IsFocus() && input->IsMouseButtonPressedImpl(0) && Pro::Math::isInside(position, size, input->GetMousePositionImpl()))
			{
				SetFocus();
			}
			
			m_renderer.AddSquare(position, size, def.windowBorderColor);
			RenderText(buffer, position);

			m_currentWindow->SetCursor({ 0, -16 });

			PopID();

		}
		
		void InputVec3(std::string label, float& x, float& y, float& z)
		{
			PushID(label);

			RenderText(label, m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({0.0f , -16.0f });
			
			InputFloat("X", x);
			InputFloat("Y", y);
			InputFloat("Z", z);
			
			PopID();

			/*
			RenderText("X", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(x, m_currentWindow->GetCursor(), 100);
			m_currentWindow->SetCursor({-16 , -16.0f });
			
			RenderText("Y", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(y, m_currentWindow->GetCursor(), 100);
			m_currentWindow->SetCursor({ -16 , -16.0f });

			RenderText("Z", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(z, m_currentWindow->GetCursor(), 100);
			m_currentWindow->SetCursor({ -16 , -16.0f });
			*/
		}
		
		void InputFloat(std::string label, float& val)
		{
			PushID(label);

			RenderText(label, m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ (float)label.size() * 8 , .0f });
			InputBox(label, val, m_currentWindow->GetCursor(), 100);
			m_currentWindow->SetCursor({ -(float)(label.size() * 8) , -16.0f });

			PopID();
		}


		void InputInt(std::string label, uint32_t& val)
		{
			PushID(label);

			RenderText(label, m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({(float) label.size() * 8 , .0f});
			InputBox(label, val, m_currentWindow->GetCursor(), 100);
			m_currentWindow->SetCursor({ -(float)(label.size() * 8) , -16.0f});
			PopID();
		}

		void InputColor(std::string label, float& r, float& g, float& b, float& a)
		{
			PushID(label);


			auto input = Pro::Application::Get().GetWindow().GetInput();

			size_t labelLength = label.size() * def.fontSize;

			RenderText(label, m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({(float) labelLength + 8, .0f});
			m_renderer.AddSquare(m_currentWindow->GetCursor(), Pro::Vec2(8, 8), Pro::Vec4(r, g, b, a));
			m_currentWindow->SetCursor({ -(float)(labelLength + 8), -16.0f});

			InputFloat("R", r);
			InputFloat("G", g);
			InputFloat("B", b);
			InputFloat("A", a);
			/*
			RenderText("R", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(r, m_currentWindow->GetCursor(), 24);
			m_currentWindow->SetCursor({ -16 , -16.0f });

			RenderText("G", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(g, m_currentWindow->GetCursor(), 24);
			m_currentWindow->SetCursor({ -16 , -16.0f });

			RenderText("B", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(b, m_currentWindow->GetCursor(), 24);
			m_currentWindow->SetCursor({ -16 , -16.0f });

			RenderText("A", m_currentWindow->GetCursor());
			m_currentWindow->SetCursor({ 16 , .0f });
			InputBox(a, m_currentWindow->GetCursor(), 24);
			m_currentWindow->SetCursor({ -16 , -16.0f });
			*/
		}

		void Image(Pro::Ref<Pro::Sprite> sprite, Pro::Vec2 size)
		{
			Pro::Vec2 position = m_currentWindow->GetPosition();
			//Pro::Vec2 size = m_currentWindow->GetSize();
			m_renderer.AddSquare(position, size, {1,1,1,1}, sprite);
		}

		void Render(const Pro::Camera& cam) { 
			m_renderer.Render(cam);
			m_ids.Reset();
		}

		bool OnEvent(Pro::Event& e)
		{
			for (int i = 0; i < m_windows.size(); i++)
			{
				if (m_windows[i]->OnEvent(e))
				{
					
					auto it = m_windows.begin();
					it += i;
					auto window = m_windows[i];
					m_windows.erase(it);
					m_windows.push_front(window);
					return true;
				}
			}
			return false;
		}
		
		std::deque<Window*> GetData()
		{
			return m_windows;
		}

		void Finish()
		{
			SaveData();
		}

		Window* GetCurrentWindow()
		{
			return m_currentWindow;
		}

		static GUI& GetInstance()
		{
			static GUI instance;
			return instance;
		}
	private:
		Pro::Input* input = nullptr;

		nlohmann::json data;
		
		Pro::Renderer2D m_renderer;
		
		Window* m_currentWindow = nullptr;
		Window* m_currentWindowGrabbed = nullptr;


		uint32_t m_focusWidgetId = 0;
		
		std::optional<std::string> m_currentInputText;
	
		float m_currentInputFloat = 0;
		uint32_t m_currentInputInt = 0;
		
		IDStack m_ids;

		std::deque<Window*> m_windows;
		
		Pro::SpriteLibrary m_font;
		
		DefaultValues def;

	};


	static void Init() { GUI::GetInstance().Init(); }
	static void SetFontTexture(Pro::SpriteLibrary m_font) { GUI::GetInstance().SetFontTexture(m_font); }
	static void Render(const Pro::Camera& cam) { GUI::GetInstance().Render(cam); }
	static void Finish() { GUI::GetInstance().Finish(); }


	static Window* Begin(std::string name) { return GUI::GetInstance().Begin(name); }
	static void End() { GUI::GetInstance().End(); }

	static void BeginMainToolbar() { GUI::GetInstance().BeginMainToolbar(); }
	static void EndMainToolbar() { GUI::GetInstance().EndMainToolbar(); }

	//Widgets
	static void Text(std::string text) { GUI::GetInstance().Text(text); }
	static bool Button(std::string text) { return  GUI::GetInstance().Button(text); }
	static void Space(int i = 1) { return  GUI::GetInstance().Space(i); }
	static void InputText(std::string label, std::string& buffer) { return  GUI::GetInstance().InputText(label, buffer); }
	static void InputInt(std::string label, uint32_t& val) { return GUI::GetInstance().InputInt(label, val); }
	static void Image(Pro::Ref<Pro::Sprite> sprite, Pro::Vec2 size) { return GUI::GetInstance().Image(sprite, size); }

	static void InputVec3(std::string label, float& x, float& y, float& z) { return  GUI::GetInstance().InputVec3(label, x, y, z); }
	static void InputColor(std::string label, float& r, float& g, float& b, float& a) { return  GUI::GetInstance().InputColor(label, r, g, b, a); }

	static Window* GetCurrentWindow() { return GUI::GetInstance().GetCurrentWindow(); };


	static std::deque<Window*> GetData()
	{
		return  GUI::GetInstance().GetData();
	}

	static bool OnEvent(Pro::Event& e)
	{
		return  GUI::GetInstance().OnEvent(e);
	}
}