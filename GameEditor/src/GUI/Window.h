#pragma once
#include <ProEngine.h>
#include <string>

namespace GUI
{


	class Window
	{
	public:
		Window(std::string name, Pro::Vec2 position, Pro::Vec2 size)
			: m_name(name), m_position(position), m_size(size), m_cursor({0,0})
		{}
		

		bool OnEvent(Pro::Event& e)
		{

			if (!m_visible) return false;

			if (Pro::MouseButtonPressedEvent* ev = dynamic_cast<Pro::MouseButtonPressedEvent*> (&e)) {
				std::cout << "a\n";

				if (Pro::Math::isInside(m_position, m_size, {ev->GetX(), ev->GetY()}))
				{
					std::cout << "a\n";
					m_grabbing = true;
					return true;
				}
			}
			
			if (Pro::MouseButtonReleasedEvent* ev = dynamic_cast<Pro::MouseButtonReleasedEvent*> (&e)) {
				if (ev->GetMouseButton() == 0)
				{
					m_grabbing = false;
				}
			}


			if (Pro::MouseMovedEvent* ev = dynamic_cast<Pro::MouseMovedEvent*> (&e)) {
				if (m_grabbing)
				{
					m_position.x += ev->GetDX();
					m_position.y += ev->GetDY();
				
				}
			}


			return false;
		}

		void Reset()
		{
			m_cursor = { 0,0 };
			m_visible = true;
		}

		Pro::Vec2	GetCursor() { return m_cursor + m_position + Pro::Vec2(10, m_size.y - 30); }
		void		SetCursor(Pro::Vec2 cursor) { m_cursor += cursor; }

		Pro::Vec2	GetPosition() { return m_position; }
		void		SetPosition(Pro::Vec2 position) { m_position = position; }
		void		AddPosition(Pro::Vec2 position) { m_position += position; }

		Pro::Vec2 GetSize() { return m_size; }
		std::string GetName() { return m_name; }

		void SetVisible(bool visibility) { m_visible = visibility; }
		bool IsVisible() { return m_visible; }

	private:

		Pro::Vec2 m_cursor;
		Pro::Vec2 m_position;
		Pro::Vec2 m_size;
		std::string m_name;
		bool m_visible = false;
		bool m_grabbing = false;
	};


}