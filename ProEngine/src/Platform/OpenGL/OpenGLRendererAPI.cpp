#include "Propch.h"
#include "OpenGLRendererAPI.h"
#include "Platform/OpenGL/gl.h"

#define PRO_ENABLE_RENDERER_LOG

namespace Pro
{
	void OpenGLMessageCallback(unsigned source, unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		std::cout << "severity: " << severity << " msg: " << message;

	}

	void OpenGLRendererAPI::Init()
	{
	#ifdef PRO_ENABLE_RENDERER_LOG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

	}

	void OpenGLRendererAPI::SetRendererSpecifications(const RendererSpecification& rendererSpecification)
	{
		if (rendererSpecification.blend) 
		{
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else 
		{
			glDisable(GL_BLEND);
		}

		if (rendererSpecification.scissor) {
			glEnable(GL_SCISSOR_TEST);
		}
		else 
		{
			glDisable(GL_SCISSOR_TEST);
		}

		if (rendererSpecification.culling) {
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		if (rendererSpecification.depth) {
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}


	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const Pro::Vec4& color) 
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}


	void OpenGLRendererAPI::DrawIndexed(const Pro::Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		PRO_PROFILE_FUNCTION();

		uint32_t count = indexCount != -1 ? indexCount: vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}