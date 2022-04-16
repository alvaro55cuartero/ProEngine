#pragma once
#include "ProEngine/Core/Window.h"
#include "ProEngine/Renderer/GraphicsContext.h"
#include "ProEngine/Events/ApplicationEvent.h"
#include <ProEngine/Math/Vec2.h>

namespace Pro
{
	typedef void (*GLproc)(void);


	class WindowsWindow : public Window
	{

	public:

		WindowsWindow(const std::string& title, const uint32_t width, const uint32_t height);

		inline unsigned int GetWidth() const override { return m_width; }
		inline unsigned int GetHeight() const override { return m_height; }

		virtual void* GetNativeWindow() const override { return m_window; }

		HDC GetNativeDeviceContext() { return m_deviceContext; }
		HGLRC GetNativeRenderingContext() { return m_rederingContext; }
		
		void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn & callback) override { m_eventCallback = callback; }

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void Win32RegisterWindow();
		
		HWND Win32CreateDummyWindow();
		void Win32SetDummyDeviceContextPixelFormat(HDC& fakeDC);
		void Win32CreateValidContext(HWND& fakeWND, HDC& fakeDC, HGLRC& fakeRC);

		void Win32CreateWindow(HWND &m_window, HDC &m_deviceContext, HGLRC &m_rederingContext);
		void Win32SetDeviceContextPixelFormat(HDC dc);
		void Win32MakeContextCurrent(HWND &window);
		void Win32ShowWindow(HWND window);
		void Win32PollEvents();
		void Win32DeleteWindow(HWND& fakeWND, HDC& fakeDC, HGLRC& fakeRC);
		static GLproc Win32ProAddress(const char* name);
		
	private:
		uint32_t m_width;
		uint32_t m_height;
		HWND m_window;
		HDC m_deviceContext;
		HGLRC m_rederingContext;

		

	private:
		EventCallbackFn m_eventCallback;

		Scope<GraphicsContext> m_context;
		const wchar_t CLASS_NAME[10] = L"ProEngine";
	};
}

