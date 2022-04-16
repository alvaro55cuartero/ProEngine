#pragma once
#include "ProEngine/Math/Vec4.h"
#include "ProEngine/Renderer/VertexArray.h"

namespace Pro 
{
	struct RendererSpecification {
		unsigned int blend = 1;
		unsigned int scissor = 0;
		unsigned int culling = 0;
		unsigned int depth = 1;
	};
	

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Vulkan = 2
		};
	public:
		virtual void Init() = 0;
		virtual void SetRendererSpecifications(const RendererSpecification& rendererSpecification) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const Pro::Vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}
