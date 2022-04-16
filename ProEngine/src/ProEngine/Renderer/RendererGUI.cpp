#include "Propch.h"
#include "RendererGUI.h"
#include "Platform/OpenGL/gl.h"
#include "ProEngine/Renderer/Shader.h"
#include "ProEngine/Renderer/Texture.h"
#include "ProEngine/Renderer/RenderCommand.h"


namespace Pro
{
	struct QuadVertex
	{
		Vec2 Position;
		Vec2 TexCoord;
		Vec4 Color;
	};

	struct RendererGUIData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		Ref<Shader> shader;
		Ref<Texture2D> texture;
		Ref<VertexArray> vertexArray;
		Ref<IndexBuffer> indexBuffer;
		Ref<VertexBuffer> vertexBuffer;
		Ref<Texture2D> WhiteTexture;


		uint32_t* IndexBufferPtr = nullptr;
		uint32_t* IndexBufferBase = nullptr;
		QuadVertex* VertexBufferBase = nullptr;
		QuadVertex* VertexBufferPtr = nullptr;

		uint32_t indexOffset = 0;
	};

	static RendererGUIData s_GUIdata;

	void RendererGUI::Init()
	{
		PRO_PROFILE_FUNCTION();

		const GLchar* vertex_shader =
			"#version 410\n"
			"layout (location = 0) in vec2 Position;\n"
			"layout (location = 1) in vec2 UV;\n"
			"layout (location = 2) in vec4 Color;\n"
			"uniform mat4 ProjMtx;\n"
			"out vec2 Frag_UV;\n"
			"out vec4 Frag_Color;\n"
			"void main()\n"
			"{\n"
			"    Frag_UV = UV;\n"
			"    Frag_Color = Color;\n"
			"    gl_Position = vec4((Position.x * 2 / 1280) - 1 , (Position.y * 2 / 720) - 1, 0, 1);\n"
			"}\n";


		const GLchar* fragment_shader =
			"#version 410\n"
			"in vec2 Frag_UV;\n"
			"in vec4 Frag_Color;\n"
			"uniform sampler2D Texture;\n"
			"layout (location = 0) out vec4 Out_Color;\n"
			"void main()\n"
			"{\n"
			"    Out_Color = Frag_Color; //* texture(Texture, Frag_UV.st);\n"
			"}\n";


		s_GUIdata.shader = Shader::Create("", vertex_shader, fragment_shader);

		s_GUIdata.vertexArray = VertexArray::Create();
		s_GUIdata.vertexBuffer = VertexBuffer::Create(s_GUIdata.MaxVertices * sizeof(QuadVertex));
		s_GUIdata.vertexBuffer->SetLayout({
			{ Pro::ShaderDataType::Float2, "Position" },
			{ Pro::ShaderDataType::Float2, "UV"},
			{ Pro::ShaderDataType::Float4, "Color"}
			});
		s_GUIdata.vertexArray->AddVertexBuffer(s_GUIdata.vertexBuffer);
		s_GUIdata.indexBuffer = IndexBuffer::Create(s_GUIdata.MaxIndices);
		s_GUIdata.vertexArray->SetIndexBuffer(s_GUIdata.indexBuffer);

		s_GUIdata.VertexBufferBase = new QuadVertex[s_GUIdata.MaxVertices];
		s_GUIdata.IndexBufferBase = new uint32_t[s_GUIdata.MaxIndices];

		s_GUIdata.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_GUIdata.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

	}

	void RendererGUI::Shutdown()
	{
		PRO_PROFILE_FUNCTION();

	}

	void RendererGUI::BeginScene(Camera& camera)
	{
		PRO_PROFILE_FUNCTION();

		RenderCommand::SetRendererSpecifications({ 1, 1, 0, 0 });
		s_GUIdata.vertexArray->Bind();
		s_GUIdata.shader->Bind();
		s_GUIdata.shader->SetInt("Texture", 0);
		s_GUIdata.shader->SetMat4("ProjMtx", camera.GetProjectionMatrix());

		s_GUIdata.VertexBufferPtr = s_GUIdata.VertexBufferBase;
		s_GUIdata.IndexBufferPtr = s_GUIdata.IndexBufferBase;

	}


	void RendererGUI::EndScene()
	{
		PRO_PROFILE_FUNCTION();
		Flush();
	}

	void RendererGUI::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		PRO_PROFILE_FUNCTION();

		AddDataToBuffer(position, size, color, 0.0f, 0.0f);
	}


	void RendererGUI::Flush()
	{
		PRO_PROFILE_FUNCTION();

		uint32_t dataSize = (uint32_t)((uint8_t*)s_GUIdata.VertexBufferPtr - (uint8_t*)s_GUIdata.VertexBufferBase);
		s_GUIdata.vertexBuffer->SetData(s_GUIdata.VertexBufferBase, dataSize);

		
		uint32_t count = (uint32_t)((uint8_t*)s_GUIdata.IndexBufferPtr - (uint8_t*)s_GUIdata.IndexBufferBase);
		s_GUIdata.indexBuffer->SetData(s_GUIdata.IndexBufferBase, count);
		s_GUIdata.indexOffset = 0;
		if (count == 0)
			return;
	
		
		/*
		for (uint32_t i = 0; i < s_data.TextureSlotIndex; i++)
			s_data.TextureSlots[i]->Bind(i);
		*/
		s_GUIdata.WhiteTexture->Bind();

		//s_ddata.TextureShader->SetMat4("u_transform", Mat4(1));

		RenderCommand::DrawIndexed(s_GUIdata.vertexArray, count);
	}

	void RendererGUI::AddDataToBuffer(const Vec2& position, const Vec2& size, const Vec4& color, float texIndex, float tilingFactor)
	{
		/*
		if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			Flush();
			ResetBuffer();
		}
		*/


		s_GUIdata.VertexBufferPtr->Position = position;
		s_GUIdata.VertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_GUIdata.VertexBufferPtr->Color = color;
		s_GUIdata.VertexBufferPtr++;

		s_GUIdata.VertexBufferPtr->Position = { position.x + size.x, position.y};
		s_GUIdata.VertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_GUIdata.VertexBufferPtr->Color = color;
		s_GUIdata.VertexBufferPtr++;

		s_GUIdata.VertexBufferPtr->Position = { position.x + size.x, position.y + size.y};
		s_GUIdata.VertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_GUIdata.VertexBufferPtr->Color = color;
		s_GUIdata.VertexBufferPtr++;

		s_GUIdata.VertexBufferPtr->Position = { position.x, position.y + size.y};
		s_GUIdata.VertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_GUIdata.VertexBufferPtr->Color = color;
		s_GUIdata.VertexBufferPtr++;

		uint32_t offset = s_GUIdata.indexOffset;

		s_GUIdata.IndexBufferPtr[0] = offset + 0;
		s_GUIdata.IndexBufferPtr[1] = offset + 1;
		s_GUIdata.IndexBufferPtr[2] = offset + 2;

		s_GUIdata.IndexBufferPtr[3] = offset + 2;
		s_GUIdata.IndexBufferPtr[4] = offset + 3;
		s_GUIdata.IndexBufferPtr[5] = offset + 0;
		s_GUIdata.IndexBufferPtr += 6;
		s_GUIdata.indexOffset += 4;
		

	}

}