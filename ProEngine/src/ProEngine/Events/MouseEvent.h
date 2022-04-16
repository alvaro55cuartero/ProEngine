#pragma once

#include "ProEngine/Events/Event.h"

namespace Pro 
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y, float dx, float dy)
			: m_mouseX(x), m_mouseY(y), m_mouseDX(dx), m_mouseDY(dy) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }
		inline float GetDX() const { return m_mouseDX; }
		inline float GetDY() const { return m_mouseDY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMoved"; }

	private:
		float m_mouseX;
		float m_mouseY;

		float m_mouseDX;
		float m_mouseDY;
	};


	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, float x, float y)
			: MouseButtonEvent(button) , m_mouseX(x), m_mouseY(y)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonPressed"; }
	
	private:
		float m_mouseX;
		float m_mouseY;
	};


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonReleased"; }
	};

	
}