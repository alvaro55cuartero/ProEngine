#include "Propch.h"
#include "ProEngine/Renderer/Renderer.h"
#include "ProEngine/Renderer/Renderer2D.h"
#include "ProEngine/Renderer/Renderer3D.h"
#include "ProEngine/Math/Mat4.h"

namespace Pro 
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		PRO_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer3D::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}


	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_viewProjection", m_SceneData->viewProjectionMatrix);
		shader->SetMat4("u_transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}