#include "Propch.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "ProEngine/Renderer/VertexArray.h"
#include "ProEngine/Renderer/Renderer.h"

namespace Pro 
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}
}