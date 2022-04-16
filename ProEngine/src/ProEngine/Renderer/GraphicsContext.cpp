#include "Propch.h"
#include "ProEngine/Renderer/GraphicsContext.h"
#include "ProEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"

namespace Pro
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>((WindowsWindow*)window);
		case RendererAPI::API::Vulkan: return CreateScope<VulkanContext>((WindowsWindow*)window);
		}
		return nullptr;
	}
}