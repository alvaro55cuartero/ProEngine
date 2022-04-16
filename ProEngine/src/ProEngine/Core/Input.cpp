#include "Propch.h"
#include "ProEngine/Core/Input.h"
#include "ProEngine/Renderer/Renderer.h"
#include "Platform/Windows/WindowsInput.h"

namespace Pro 
{
	Input* Input::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new WindowsInput();
		}
		return nullptr;
	}
}