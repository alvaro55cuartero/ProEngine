#pragma once

#include "ProEngine/Events/Event.h"
#include "ProEngine/Core/Input.h"
#include "ProEngine/Core/Timer.h"
#include "ProEngine/Math/Vec2.h"

#include <cstdint>
#include <string>
#include <functional>

namespace Pro 
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		static Window* Create(const std::string& title = "ProEngine",  const uint32_t width = 1280, const uint32_t height = 720);
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		
		virtual void* GetNativeWindow() const = 0;

		Input* GetInput() { return m_input; };
		Timer* GetTimer() { return m_timer; };
		Vec2 GetMousePos() { return m_mousePos; };

	protected:
		Input* m_input;
		Timer* m_timer;
		Vec2 m_mousePos;
	
	};
}