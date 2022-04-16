#include "Propch.h"
#include "Renderer3D.h"

#include <ProEngine/Renderer/VertexArray.h>
#include <ProEngine/Renderer/Shader.h>
#include <Platform/OpenGL/OpenGLTexture.h>
#include <ProEngine/Renderer/RenderCommand.h>

namespace Pro {

	struct Vertex
	{
		Vec3 Position;
		Vec4 Color;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxTriangles = 20000;
		static const uint32_t MaxVertices = MaxTriangles * 3;
		// static const uint32_t MaxIndices = MaxTriangles * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> vertexArray;
		Ref<VertexBuffer> vertexBuffer;
		Ref<IndexBuffer> indexBuffer;

		Ref<Texture2D> WhiteTexture;

		Ref<Shader> TextureShader;

		uint32_t QuadIndexCount = 0;
		//QuadVertex* QuadVertexBufferBase = nullptr;
		//QuadVertex* VertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		Vec4 QuadVertexPositions[4];

	};

	static Renderer2DData s_3Ddata;

	void Renderer3D::Init()
	{
		PRO_PROFILE_FUNCTION();

		s_3Ddata.vertexArray = VertexArray::Create();
		s_3Ddata.vertexBuffer = VertexBuffer::Create(s_3Ddata.MaxVertices * sizeof(Vertex));
		s_3Ddata.vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
			});
		s_3Ddata.vertexArray->AddVertexBuffer(s_3Ddata.vertexBuffer);

		s_3Ddata.indexBuffer = IndexBuffer::Create(1000000);
		s_3Ddata.vertexArray->SetIndexBuffer(s_3Ddata.indexBuffer);

		s_3Ddata.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_3Ddata.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_3Ddata.MaxTextureSlots];
		for (uint32_t i = 0; i < s_3Ddata.MaxTextureSlots; i++)
			samplers[i] = i;

		s_3Ddata.TextureShader = Shader::Create("assets/shaders/FlatColor.glsl");
		s_3Ddata.TextureShader->Bind();
		//s_3Ddata.TextureShader->SetIntArray("u_textures", samplers, s_3Ddata.MaxTextureSlots);

		s_3Ddata.TextureSlots[0] = s_3Ddata.WhiteTexture;
	}

	void Renderer3D::Shutdown()
	{
		
	
	}

	void Renderer3D::BeginScene(const Camera& camera, const Mat4& transform)
	{
		RenderCommand::SetRendererSpecifications({});

		s_3Ddata.vertexArray->Bind();

		s_3Ddata.TextureShader->Bind();
		Mat4 a = { 0.97,0,0,0,
				  0,1.7,0,0,
				  0,0,0.7,1,
				  0,0,-1.02,0 };

		//a = a * camera.GetViewMatrix();
		//a = camera.GetViewProjectionMatrix();
		s_3Ddata.TextureShader->SetMat4("u_viewProjection", a);

		//s_3Ddata.QuadIndexCount = 0;
		//s_3Ddata.VertexBufferPtr = s_3Ddata.vertexBufferBase;
		//s_3Ddata.TextureSlotIndex = 1;
	}

	void Renderer3D::EndScene()
	{
		PRO_PROFILE_FUNCTION();

		//uint32_t dataSize = (uint32_t)((uint8_t*)s_3Ddata.VertexBufferPtr - (uint8_t*)s_3Ddata.QuadVertexBufferBase);
		Vertex* a = new Vertex[3];
		a[0].Position = { 0, 0, 0 };
		a[0].Color = { 1, 0, 0, 1 };
		a[1].Position = { 1, 1, 0 };
		a[1].Color = { 1, 0, 0, 1 };
		a[2].Position = { 0, 1, 0 };
		a[2].Color = { 1, 0, 0, 1 };

		s_3Ddata.vertexBuffer->SetData(a, 3);

		int* b = new int[3];
		b[0] = 0;
		b[1] = 1;
		b[2] = 2;

		s_3Ddata.indexBuffer->SetData(b, 3);

		//for (uint32_t i = 0; i < s_3Ddata.TextureSlotIndex; i++)
		//	s_3Ddata.TextureSlots[i]->Bind(i);

		//s_ddata.TextureShader->SetMat4("u_transform", Mat4(1));

		RenderCommand::DrawIndexed(s_3Ddata.vertexArray, s_3Ddata.QuadIndexCount);
	}

	void Renderer3D::Flush()
	{

	}
}