#include "Propch.h"
#include "ProEngine/Renderer/RenderCommand.h"
#include "ProEngine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace Pro 
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}

