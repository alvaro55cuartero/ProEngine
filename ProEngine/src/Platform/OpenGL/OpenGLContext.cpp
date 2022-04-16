#include "Propch.h"
#include "OpenGLContext.h"


namespace Pro
{

	OpenGLContext::OpenGLContext(WindowsWindow* window)
		: m_window(window)
	{
	}

	void OpenGLContext::Init()
	{
		PRO_PROFILE_FUNCTION();

		wglMakeCurrent(m_window->GetNativeDeviceContext(), m_window->GetNativeRenderingContext());
		//glfwMakeContextCurrent(m_WindowHandle);
		//int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	
	void OpenGLContext::SwapBuffers()
	{
		PRO_PROFILE_FUNCTION();

		//SwapBuffers(m_window->GetNativeDeviceContext());
	}

}