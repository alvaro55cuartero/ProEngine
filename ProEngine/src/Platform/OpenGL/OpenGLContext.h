#pragma once
#include "ProEngine/Renderer/GraphicsContext.h"
#include "Platform/Windows/WindowsWindow.h"
#include <Windows.h>

namespace Pro 
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(WindowsWindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		WindowsWindow* m_window;

	};
}


