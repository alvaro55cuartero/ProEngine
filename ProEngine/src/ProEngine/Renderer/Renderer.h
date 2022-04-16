#pragma once

#include "ProEngine/Renderer/Cameras/OrthographicCamera.h"
#include "ProEngine/Renderer/RenderCommand.h"
#include "ProEngine/Renderer/VertexArray.h"
#include "ProEngine/Renderer/Shader.h"

namespace Pro
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();
		
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Mat4& transform = Mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData
		{
			Mat4 viewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}