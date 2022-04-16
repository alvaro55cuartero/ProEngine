#pragma once
#include "ProEngine/Renderer/RendererAPI.h"

namespace Pro
{

	

	class OpenGLRendererAPI : public RendererAPI
	{

		virtual void Init() override;
		virtual void SetRendererSpecifications(const RendererSpecification& rendererSpecification) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;
		virtual void SetClearColor(const Pro::Vec4& color) override;

		virtual void DrawIndexed(const Pro::Ref<VertexArray>& vertexArray, uint32_t count) override;

	private:
		RendererSpecification m_rendererSpecification;
	};
}

