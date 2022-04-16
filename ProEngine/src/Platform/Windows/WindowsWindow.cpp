#include "Propch.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/gl.h"
#include "ProEngine/Events/KeyEvents.h"
#include "ProEngine/Events/MouseEvent.h"
#include "Platform/Windows/WindowsInput.h"
#include "ProEngine/Core/Timer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>







#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define ERROR_INVALID_VERSION_ARB               0x2095
#define ERROR_INVALID_PROFILE_ARB               0x2096
#define WGL_NUMBER_PIXEL_FORMATS_ARB            0x2000
#define WGL_DRAW_TO_WINDOW_ARB                  0x2001
#define WGL_DRAW_TO_BITMAP_ARB                  0x2002
#define WGL_ACCELERATION_ARB                    0x2003
#define WGL_NEED_PALETTE_ARB                    0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB             0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB              0x2006
#define WGL_SWAP_METHOD_ARB                     0x2007
#define WGL_NUMBER_OVERLAYS_ARB                 0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                0x2009
#define WGL_TRANSPARENT_ARB                     0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB           0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB         0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB          0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB         0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB         0x203B
#define WGL_SHARE_DEPTH_ARB                     0x200C
#define WGL_SHARE_STENCIL_ARB                   0x200D
#define WGL_SHARE_ACCUM_ARB                     0x200E
#define WGL_SUPPORT_GDI_ARB                     0x200F
#define WGL_SUPPORT_OPENGL_ARB                  0x2010
#define WGL_DOUBLE_BUFFER_ARB                   0x2011
#define WGL_STEREO_ARB                          0x2012
#define WGL_PIXEL_TYPE_ARB                      0x2013
#define WGL_COLOR_BITS_ARB                      0x2014
#define WGL_RED_BITS_ARB                        0x2015
#define WGL_RED_SHIFT_ARB                       0x2016
#define WGL_GREEN_BITS_ARB                      0x2017
#define WGL_GREEN_SHIFT_ARB                     0x2018
#define WGL_BLUE_BITS_ARB                       0x2019
#define WGL_BLUE_SHIFT_ARB                      0x201A
#define WGL_ALPHA_BITS_ARB                      0x201B
#define WGL_ALPHA_SHIFT_ARB                     0x201C
#define WGL_ACCUM_BITS_ARB                      0x201D
#define WGL_ACCUM_RED_BITS_ARB                  0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                 0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                0x2021
#define WGL_DEPTH_BITS_ARB                      0x2022
#define WGL_STENCIL_BITS_ARB                    0x2023
#define WGL_AUX_BUFFERS_ARB                     0x2024
#define WGL_NO_ACCELERATION_ARB                 0x2025
#define WGL_GENERIC_ACCELERATION_ARB            0x2026
#define WGL_FULL_ACCELERATION_ARB               0x2027
#define WGL_SWAP_EXCHANGE_ARB                   0x2028
#define WGL_SWAP_COPY_ARB                       0x2029
#define WGL_SWAP_UNDEFINED_ARB                  0x202A
#define WGL_TYPE_RGBA_ARB                       0x202B
#define WGL_TYPE_COLORINDEX_ARB                 0x202C
#define GLX_SAMPLE_BUFFERS_ARB                  100000
#define GLX_SAMPLES_ARB                         100001
#define WGL_SAMPLE_BUFFERS_ARB                  0x2041
#define WGL_SAMPLES_ARB                         0x2042
#define MULTISAMPLE_ARB                         0x809D
#define SAMPLE_ALPHA_TO_COVERAGE_ARB            0x809E
#define SAMPLE_ALPHA_TO_ONE_ARB                 0x809F
#define SAMPLE_COVERAGE_ARB                     0x80A0
#define MULTISAMPLE_BIT_ARB                     0x20000000
#define SAMPLE_BUFFERS_ARB                      0x80A8
#define SAMPLES_ARB                             0x80A9
#define SAMPLE_COVERAGE_VALUE_ARB               0x80AA
#define SAMPLE_COVERAGE_INVERT_ARB              0x80AB



#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_VERSION 0x1F02 


namespace Pro
{

	typedef HGLRC(*PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

	typedef BOOL(*PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC, const int*, const float*, unsigned int, int*, unsigned int*);
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;


	void glLoadWGLFunctions()
	{
		PRO_PROFILE_FUNCTION();

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

	}

	Window* Window::Create(const std::string& title, const uint32_t width, const uint32_t height)
	{
		return new WindowsWindow(title, width, height);
	}

	WindowsWindow::WindowsWindow(const std::string& title, const uint32_t width, const uint32_t height)
		:m_width(width), m_height(height)
	{
		PRO_PROFILE_FUNCTION();
		m_input = Input::Create();
		m_timer = Timer::Create();

#if 0



		GLFWwindow* window;

		if (!glfwInit()) //HECHO con TODOS
			return;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); // HECHO con TODOS
		if (!window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwGetTime();
		glfwSetCursorPosCallback
			glfwSetMouseButtonCallback


			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{
				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT);

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();
			}

		glfwTerminate();
		return;


#else


		HWND fakeWND;
		HDC fakeDC;
		HGLRC fakeRC;

		Win32CreateValidContext(fakeWND, fakeDC, fakeRC);
		glLoadWGLFunctions();
		Win32DeleteWindow(fakeWND, fakeDC, fakeRC);

		Win32CreateWindow(m_window, m_deviceContext, m_rederingContext);

		//glLoadFunctions(Win32ProAddress);
		int status = gladLoadGLLoader((GLADloadproc)Win32ProAddress);
		SetPropW(m_window, L"ProEngine", this);


		m_context = GraphicsContext::Create(this);

		m_context->Init();

		{
			PRO_PROFILE_SCOPE("Show Window");
			ShowWindow(m_window, 1);
		}

#endif
	}

	void WindowsWindow::OnUpdate()
	{
		PRO_PROFILE_FUNCTION();

		GetInput()->Update();
		Win32PollEvents();
		SwapBuffers(m_deviceContext);
		//m_context->SwapBuffers();
	}


	LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

		WindowsWindow* window = (WindowsWindow*)GetProp(hwnd, L"ProEngine");


		switch (uMsg) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			int action = (HIWORD(lParam) & KF_UP) ? 0 : 1;

			int scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));

			if (!scancode) scancode = MapVirtualKey((UINT)wParam, MAPVK_VK_TO_VSC);

			auto input = (WindowsInput*)window->GetInput();
			int key = input->GetKeycode((UINT)wParam);


			bool repeated = false;

			if (action == PRO_RELEASE && input->GetKey(key) == PRO_RELEASE)
				return 0;

			if (action == PRO_PRESS && input->GetKey(key) == PRO_PRESS)
			{
				KeyPressedEvent event(key, 1);
				window->m_eventCallback(event);
				return 0;
			}


			input->SetKey(key, (char)action);

			if (repeated) {
				action = PRO_REPEAT;
			}

			if (action == PRO_RELEASE)
			{
				KeyReleasedEvent event(key);
				window->m_eventCallback(event);
				return 0;
			}

			if (action == PRO_PRESS)
			{
				KeyPressedEvent event(key, 0);
				window->m_eventCallback(event);
				return 0;
			}

		} break;

		case WM_CLOSE:
		{
			WindowCloseEvent event;
			window->m_eventCallback(event);
		} break;

		case WM_SIZE:
		{
			const int width = LOWORD(lParam);
			const int height = HIWORD(lParam);

			WindowResizeEvent event(width, height);
			if (window->m_eventCallback)
				window->m_eventCallback(event);

		}break;

		case WM_MOUSEMOVE:
		{

			const int x = GET_X_LPARAM(lParam);
			const int y = window->GetHeight() - GET_Y_LPARAM(lParam);



			const int dx = x - window->m_mousePos.x;
			const int dy = y - window->m_mousePos.y;


			window->m_mousePos.x = x;
			window->m_mousePos.y = y;
			

			MouseMovedEvent event(x, y, dx, dy);

			if (window->m_eventCallback)
				window->m_eventCallback(event);
		}break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		{
			int button;
			if (uMsg == WM_LBUTTONDOWN)							button = PRO_MOUSE_BUTTON_LEFT;
			else if (uMsg == WM_RBUTTONDOWN)					button = PRO_MOUSE_BUTTON_RIGHT;
			else if (uMsg == WM_MBUTTONDOWN)					button = PRO_MOUSE_BUTTON_MIDDLE;
			else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)	button = PRO_MOUSE_BUTTON_4;
			else												button = PRO_MOUSE_BUTTON_5;
			
			
			auto input = (WindowsInput*)window->GetInput();
			int key = input->GetKeycode(button);


			input->SetKey(key, (char)PRO_PRESS);

			const int x = GET_X_LPARAM(lParam);
			const int y = window->GetHeight() - GET_Y_LPARAM(lParam);

			MouseButtonPressedEvent event(button, x, y);
			if (window->m_eventCallback)
				window->m_eventCallback(event);
		}break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		{
			int button;

			if (uMsg == WM_LBUTTONUP)							button = GLFW_MOUSE_BUTTON_LEFT;
			else if (uMsg == WM_RBUTTONUP)						button = GLFW_MOUSE_BUTTON_RIGHT;
			else if (uMsg == WM_MBUTTONUP)						button = GLFW_MOUSE_BUTTON_MIDDLE;
			else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)	button = GLFW_MOUSE_BUTTON_4;
			else												button = GLFW_MOUSE_BUTTON_5;

			auto input = (WindowsInput*)window->GetInput();
			int key = input->GetKeycode(button);
			input->SetKey(key, (char)PRO_RELEASE);

			MouseButtonReleasedEvent event(button);
			if (window->m_eventCallback)
				window->m_eventCallback(event);

		}break;

		case WM_CHAR:
		{
			auto input = (WindowsInput*)window->GetInput();

			input->AddCharToQueue((char)wParam);
		}
		break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	void WindowsWindow::Win32RegisterWindow()
	{
		PRO_PROFILE_FUNCTION();

		WNDCLASSEX wc = { };

		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;


		wc.lpfnWndProc = (WNDPROC)WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = CLASS_NAME;

		wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), L"GLFW_ICON", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

		if (!wc.hIcon)
		{
			wc.hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		}

		RegisterClassEx(&wc);

	}

	void WindowsWindow::Win32CreateValidContext(HWND& fakeWND, HDC& fakeDC, HGLRC& fakeRC)
	{
		PRO_PROFILE_FUNCTION();

		Win32RegisterWindow();

		fakeWND = Win32CreateDummyWindow();

		//---create fake contex
		fakeDC = GetDC(fakeWND);

		Win32SetDummyDeviceContextPixelFormat(fakeDC);
		{
			PRO_PROFILE_SCOPE("Create Fake Context");
			fakeRC = wglCreateContext(fakeDC);
			if (fakeRC == 0) return;

			if (wglMakeCurrent(fakeDC, fakeRC) == false) return;
		}
	}

	HWND WindowsWindow::Win32CreateDummyWindow()
	{
		PRO_PROFILE_FUNCTION();
		HWND window = CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, L"ProEngine", WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 1, 1, NULL, NULL, GetModuleHandle(NULL), NULL);

		if (window == NULL) return nullptr;

		return window;
	}

	void WindowsWindow::Win32SetDummyDeviceContextPixelFormat(HDC& fakeDC)
	{
		PRO_PROFILE_FUNCTION();

		PIXELFORMATDESCRIPTOR fakePFD;
		ZeroMemory(&fakePFD, sizeof(fakePFD));
		fakePFD.nSize = sizeof(fakePFD);
		fakePFD.nVersion = 1;
		fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		fakePFD.iPixelType = PFD_TYPE_RGBA;
		fakePFD.cColorBits = 32;
		fakePFD.cAlphaBits = 8;
		fakePFD.cDepthBits = 24;

		int fakePFDID;
		{
			PRO_PROFILE_SCOPE("ChoosePixelFormat");
			fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
		}

		if (fakePFDID == 0) return;

		if (SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false) return;
	}

	void WindowsWindow::Win32DeleteWindow(HWND& fakeWND, HDC& fakeDC, HGLRC& fakeRC)
	{
		PRO_PROFILE_FUNCTION();

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeRC);
		ReleaseDC(fakeWND, fakeDC);
		DestroyWindow(fakeWND);
	}

	void WindowsWindow::Win32CreateWindow(HWND& window, HDC& deviceContext, HGLRC& rederingContext) {
		PRO_PROFILE_FUNCTION();

		RECT rc = {
		0, 0, m_width, m_height
		};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		//TODO: Revisar Opciones
		window = CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, L"ProEngine", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, GetModuleHandle(NULL), NULL);



		//TODO: ERROR HANDLING
		if (window == NULL) return;


		deviceContext = GetDC(window);

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, true,
			WGL_SUPPORT_OPENGL_ARB, true,
			WGL_DOUBLE_BUFFER_ARB, true,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_SAMPLE_BUFFERS_ARB, true,
			WGL_SAMPLES_ARB, 4,
			0
		};


		int pixelFormatID;
		UINT numFormats;
		bool status = wglChoosePixelFormatARB(deviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

		if (status == false || numFormats == 0) return;

		PIXELFORMATDESCRIPTOR PFD;
		DescribePixelFormat(deviceContext, pixelFormatID, sizeof(PFD), &PFD);
		SetPixelFormat(deviceContext, pixelFormatID, &PFD);


		int  contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		rederingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttribs);
		if (rederingContext == NULL) return;


		if (!wglMakeCurrent(deviceContext, rederingContext))  return;

	}

	void WindowsWindow::Win32SetDeviceContextPixelFormat(HDC dc)
	{
		PRO_PROFILE_FUNCTION();

		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;

		SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd);
	}

	void WindowsWindow::Win32MakeContextCurrent(HWND& window)
	{

		//wglMakeCurrent(deviceContext, );
	}

	void WindowsWindow::Win32ShowWindow(HWND window)
	{
		PRO_PROFILE_FUNCTION();

		ShowWindow(window, SW_SHOWNA);
	}

	void WindowsWindow::Win32PollEvents()
	{
		PRO_PROFILE_FUNCTION();

		MSG msg;
		HWND handle;

		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	GLproc WindowsWindow::Win32ProAddress(const char* name)
	{
		PRO_PROFILE_FUNCTION();

		const GLproc proc = (GLproc)wglGetProcAddress(name);
		if (proc)
			return proc;

		HINSTANCE gl = LoadLibrary(L"opengl32.dll");
		return (GLproc)GetProcAddress(gl, name);
	}

}