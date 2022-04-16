#pragma once

#include "ProEngine/Math/Vec4.h"
#include "ProEngine/Renderer/RendererAPI.h"
#include "ProEngine/Renderer/VertexArray.h"

namespace Pro 
{

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetRendererSpecifications(const RendererSpecification& rendererSpecification)
		{
			s_RendererAPI->SetRendererSpecifications(rendererSpecification);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const Vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			vertexArray->Bind();
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};



}
