#include "Propch.h"
#include "ProEngine/Renderer/Renderer2D.h"



namespace Pro 
{

	/*

	struct QuadVertex
	{
		Vec3 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps
		
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* VertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		Vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_ddata;

	void Renderer2D::Init()
	{
		PRO_PROFILE_FUNCTION();

		s_ddata.QuadVertexArray = VertexArray::Create();

		s_ddata.QuadVertexBuffer = VertexBuffer::Create(s_ddata.MaxVertices * sizeof(QuadVertex));
		s_ddata.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" },
			{ ShaderDataType::Float2, "a_textCoord" },
			{ ShaderDataType::Float, "a_textIndex" },
			{ ShaderDataType::Float, "a_tilingFactor" }
			});
		s_ddata.QuadVertexArray->AddVertexBuffer(s_ddata.QuadVertexBuffer);

		s_ddata.QuadVertexBufferBase = new QuadVertex[s_ddata.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_ddata.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_ddata.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_ddata.MaxIndices);

		
		s_ddata.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_ddata.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_ddata.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_ddata.MaxTextureSlots];
		for (uint32_t i = 0; i < s_ddata.MaxTextureSlots; i++)
			samplers[i] = i;

		s_ddata.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_ddata.TextureShader->Bind();
		s_ddata.TextureShader->SetIntArray("u_textures", samplers, s_ddata.MaxTextureSlots);

		s_ddata.TextureSlots[0] = s_ddata.WhiteTexture;
		
		s_ddata.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_ddata.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_ddata.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_ddata.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		PRO_PROFILE_FUNCTION();

		delete[] s_ddata.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		PRO_PROFILE_FUNCTION();

		RenderCommand::SetRendererSpecifications({});
		
		s_ddata.QuadVertexArray->Bind();

		s_ddata.TextureShader->Bind();


		s_ddata.TextureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		s_ddata.QuadIndexCount = 0;
		s_ddata.VertexBufferPtr = s_ddata.QuadVertexBufferBase;
		s_ddata.TextureSlotIndex = 1;
	}

	void Renderer2D::BeginScene(const Camera& camera, const Mat4& transform)
	{
		PRO_PROFILE_FUNCTION();

		RenderCommand::SetRendererSpecifications({});

		s_ddata.QuadVertexArray->Bind();

		s_ddata.TextureShader->Bind();

		s_ddata.TextureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		s_ddata.QuadIndexCount = 0;
		s_ddata.VertexBufferPtr = s_ddata.QuadVertexBufferBase;
		s_ddata.TextureSlotIndex = 1;
	}


	void Renderer2D::EndScene()
	{
		PRO_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer2D::Flush()
	{
		PRO_PROFILE_FUNCTION();
		
		uint32_t dataSize = (uint32_t)((uint8_t*)s_ddata.VertexBufferPtr - (uint8_t*)s_ddata.QuadVertexBufferBase);
		s_ddata.QuadVertexBuffer->SetData(s_ddata.QuadVertexBufferBase, dataSize);

		if (s_ddata.QuadIndexCount == 0)
			return;

		for (uint32_t i = 0; i < s_ddata.TextureSlotIndex; i++)
			s_ddata.TextureSlots[i]->Bind(i);

		//s_ddata.TextureShader->SetMat4("u_transform", Mat4(1));

		RenderCommand::DrawIndexed(s_ddata.QuadVertexArray, s_ddata.QuadIndexCount);
	}


	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color)
	{
		PRO_PROFILE_FUNCTION();

		AddDataToBuffer(position, size, color, 0.0f, 0.0f);
	}

	void Renderer2D::DrawQuad(const Mat4& transform, const Vec4& color)
	{
		PRO_PROFILE_FUNCTION();

		AddDataToBuffer(transform, color, 0.0f, 0.0f);
	}
	

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{
		PRO_PROFILE_FUNCTION();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_ddata.TextureSlotIndex; i++)
		{
			if (*s_ddata.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_ddata.TextureSlotIndex;
			s_ddata.TextureSlots[s_ddata.TextureSlotIndex] = texture;
			s_ddata.TextureSlotIndex++;
		}

		AddDataToBuffer(position, size, tintColor, textureIndex, tilingFactor);

		//Mat4 transform = Math::translate(Mat4(1.0f), position) * Math::scale(Mat4(1.0f), { size.x, size.y, 1.0f });
		//s_ddata.TextureShader->SetMat4("u_transform", transform);
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, const Vec2& uvPos, const Vec2& uvSize, float tilingFactor, const Vec4& tintColor)
	{
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, texture, uvPos, uvSize, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, const Vec2& uvPos, const Vec2& uvSize, float tilingFactor, const Vec4& tintColor)
	{
		PRO_PROFILE_FUNCTION();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_ddata.TextureSlotIndex; i++)
		{
			if (*s_ddata.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_ddata.TextureSlotIndex;
			s_ddata.TextureSlots[s_ddata.TextureSlotIndex] = texture;
			s_ddata.TextureSlotIndex++;
		}

		AddDataToBuffer(position, size, tintColor, textureIndex, tilingFactor);
	}


	void Renderer2D::DrawRotatedQuad(const Vec2& position, const Vec2& size, float rotation, const Vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	
	void Renderer2D::DrawRotatedQuad(const Vec3& position, const Vec2& size, float rotation, const Vec4& color)
	{
		PRO_PROFILE_FUNCTION();

		const float textureIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;


		Mat4 transform = Math::translate(Mat4(1.0f), { position.x, position.y, position.z }) 
			* Math::rotate(Mat4(1), Math::radians(rotation), { 0.0f, 0.0f, 1.0f }) 
			* Math::scale(Mat4(1.0f), { size.x, size.y, 1.0f });


		
		s_ddata.VertexBufferPtr->Position = transform * s_ddata.QuadVertexPositions[0];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_ddata.VertexBufferPtr->TexIndex = textureIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;
		  
		s_ddata.VertexBufferPtr->Position = transform * s_ddata.QuadVertexPositions[1];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_ddata.VertexBufferPtr->TexIndex = textureIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;
		  
		s_ddata.VertexBufferPtr->Position = transform * s_ddata.QuadVertexPositions[2];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_ddata.VertexBufferPtr->TexIndex = textureIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;
		  
		s_ddata.VertexBufferPtr->Position = transform * s_ddata.QuadVertexPositions[3];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_ddata.VertexBufferPtr->TexIndex = textureIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;
		

		s_ddata.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const Vec2& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);

	}

	void Renderer2D::DrawRotatedQuad(const Vec3& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{

	}

	void Renderer2D::DrawQuadImmediate(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		DrawQuadImmediate({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuadImmediate(const Vec3& position, const Vec2& size, const Vec4& color)
	{
		PRO_PROFILE_FUNCTION();

		AddDataToBuffer(position, size, color, 0.0f, 0.0f);
		Flush();
	}

	void Renderer2D::DrawQuadImmediate(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{
		DrawQuadImmediate({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuadImmediate(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const Vec4& tintColor)
	{
		PRO_PROFILE_FUNCTION();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_ddata.TextureSlotIndex; i++)
		{
			if (*s_ddata.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_ddata.TextureSlotIndex;
			s_ddata.TextureSlots[s_ddata.TextureSlotIndex] = texture;
			s_ddata.TextureSlotIndex++;
		}

		AddDataToBuffer(position, size, tintColor, textureIndex, tilingFactor);

		Flush();
	}


	void Renderer2D::AddDataToBuffer(const Mat4& transform, const Vec4& color, float texIndex, float tilingFactor, const Vec2& uvPos, const Vec2& uvSize)
	{
		PRO_PROFILE_FUNCTION();

		const Vec4 positions[] = { {-0.5f, -0.5f, 0.0f, 1.0f}, { 0.5f, -0.5f, 0.0f, 1.0f }, { 0.5f,  0.5f, 0.0f, 1.0f }, { -0.5f,  0.5f, 0.0f, 1.0f } };

		if (s_ddata.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			Flush();
			ResetBuffer();
		}

		s_ddata.VertexBufferPtr->Position = transform * positions[0];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = uvPos;
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = transform * positions[1];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x + uvSize.x, uvPos.y };
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = transform * positions[2];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x + uvSize.x, uvPos.y + uvSize.y };
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = transform * positions[3];
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x, uvPos.y + uvSize.y };
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.QuadIndexCount += 6;

		s_ddata.Stats.QuadCount++;
	}

	void Renderer2D::AddDataToBuffer(const Vec3& position, const Vec2& size, const Vec4& color, float texIndex, float tilingFactor, const Vec2& uvPos, const Vec2& uvSize)
	{
		PRO_PROFILE_FUNCTION();

		if (s_ddata.QuadIndexCount >= Renderer2DData::MaxIndices) 
		{
			Flush();
			ResetBuffer();
		}
			

		s_ddata.VertexBufferPtr->Position = position;
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = uvPos;
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x + uvSize.x, uvPos.y};
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x + uvSize.x, uvPos.y + uvSize.y };
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.VertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_ddata.VertexBufferPtr->Color = color;
		s_ddata.VertexBufferPtr->TexCoord = { uvPos.x, uvPos.y + uvSize.y };
		s_ddata.VertexBufferPtr->TexIndex = texIndex;
		s_ddata.VertexBufferPtr->TilingFactor = tilingFactor;
		s_ddata.VertexBufferPtr++;

		s_ddata.QuadIndexCount += 6;

		s_ddata.Stats.QuadCount++;

	}

	void Renderer2D::ResetBuffer()
	{
		s_ddata.QuadIndexCount = 0;
		s_ddata.VertexBufferPtr = s_ddata.QuadVertexBufferBase;

		s_ddata.TextureSlotIndex = 1;
	}
	*/

	void Renderer2D::Init() {
		m_shader = Pro::Shader::Create("Assets/Shaders/Shader.glsl");
		m_vao = Pro::VertexArray::Create();
		m_vbo = Pro::VertexBuffer::Create(100000);
		m_vbo->SetLayout({
			{ Pro::ShaderDataType::Float3, "a_position" },
			{ Pro::ShaderDataType::Float4, "a_color"    },
			{ Pro::ShaderDataType::Float2, "a_textCoord"},
			{ Pro::ShaderDataType::Float,  "a_textIndex"},
			});

		m_ibo = Pro::IndexBuffer::Create(100000);

		m_vao->AddVertexBuffer(m_vbo);
		m_vao->SetIndexBuffer(m_ibo);


		for (int i = 0; i < 32; i++) {
			m_texturesIndices[i] = i;

		}


		//White Texture
		Pro::Ref<Pro::Texture2D> texture = Pro::Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		texture->SetData(&textureData, sizeof(uint32_t));
		m_whiteTexture = Pro::SpriteSheet::Create("White", "", texture, { 1,1 });
		m_textures[0] = m_whiteTexture;

		m_whiteSprite = Pro::Sprite::Create("FULL", { 1, 1 }, { 1, 1 }, m_whiteTexture);

	}

	void Renderer2D::Render(const Camera& cam)
	{
		PRO_PROFILE_FUNCTION();

		Pro::RenderCommand::SetRendererSpecifications({ 1,0,0,0 });
		m_vao->Bind();
		m_vbo->SetData(m_vertices.data(), (uint32_t)m_vertices.size() * sizeof(float));
		m_ibo->SetData(m_indices.data(), (uint32_t)m_indices.size() * sizeof(uint32_t));


		for (int i = 0; i < m_textures.size(); i++)
			if (m_textures[i]) m_textures[i]->Bind(i);

		m_shader->Bind();
		m_shader->SetMat4("u_transform", Pro::Mat4(1));
		m_shader->SetMat4("u_view", cam.GetViewMatrix());
		m_shader->SetMat4("u_projection", cam.GetProjectionMatrix());
		m_shader->SetIntArray("u_textures", m_texturesIndices, 32);
		Pro::RenderCommand::DrawIndexed(m_vao, (uint32_t)m_indices.size());

		m_vertices.clear();
		m_indices.clear();
		m_SpriteCount = 0;
	}


	void Renderer2D::AddSquare(Pro::Vec3 position, Pro::Vec2 size, Pro::Vec4 color, Pro::Ref<Pro::SpriteSheet>& texture)
	{

		AddSquare(position, size, color, m_whiteSprite);

	}

	void Renderer2D::AddSquare(Pro::Vec3 position, Pro::Vec2 size, Pro::Vec4 color)
	{
		AddSquare(position, size, color, m_whiteSprite);

	}

	void Renderer2D::AddSquare(Pro::Vec3 position, Pro::Vec2 size, Pro::Vec4 color, Pro::Ref<Pro::Sprite> sprite)
	{

		auto texture = sprite->GetSpriteSheet();
		int textureIndex = GetTextureIndex(texture);


		m_vertices.push_back(position.x);
		m_vertices.push_back(position.y);
		m_vertices.push_back(position.z);

		m_vertices.push_back(color.x);
		m_vertices.push_back(color.y);
		m_vertices.push_back(color.z);
		m_vertices.push_back(color.w);

		m_vertices.push_back(sprite->GetPos().x);
		m_vertices.push_back(sprite->GetPos().y);

		m_vertices.push_back(textureIndex);



		m_vertices.push_back(position.x);
		m_vertices.push_back(position.y + size.y);
		m_vertices.push_back(position.z);

		m_vertices.push_back(color.x);
		m_vertices.push_back(color.y);
		m_vertices.push_back(color.z);
		m_vertices.push_back(color.w);

		m_vertices.push_back(sprite->GetPos().x);
		m_vertices.push_back(sprite->GetDim().y);

		m_vertices.push_back(textureIndex);



		m_vertices.push_back(position.x + size.x);
		m_vertices.push_back(position.y);
		m_vertices.push_back(position.z);

		m_vertices.push_back(color.x);
		m_vertices.push_back(color.y);
		m_vertices.push_back(color.z);
		m_vertices.push_back(color.w);

		m_vertices.push_back(sprite->GetDim().x);
		m_vertices.push_back(sprite->GetPos().y);

		m_vertices.push_back(textureIndex);



		m_vertices.push_back(position.x + size.x);
		m_vertices.push_back(position.y + size.y);
		m_vertices.push_back(position.z);

		m_vertices.push_back(color.x);
		m_vertices.push_back(color.y);
		m_vertices.push_back(color.z);
		m_vertices.push_back(color.w);

		m_vertices.push_back(sprite->GetDim().x);
		m_vertices.push_back(sprite->GetDim().y);

		m_vertices.push_back(textureIndex);




		m_indices.push_back((m_SpriteCount * 4) + 0);
		m_indices.push_back((m_SpriteCount * 4) + 1);
		m_indices.push_back((m_SpriteCount * 4) + 2);
		m_indices.push_back((m_SpriteCount * 4) + 2);
		m_indices.push_back((m_SpriteCount * 4) + 1);
		m_indices.push_back((m_SpriteCount * 4) + 3);

		m_SpriteCount++;
	}

	void Renderer2D::AddText(std::string text, Pro::Vec3 position, Pro::Vec4 color, int fontSize, Pro::SpriteLibrary spriteLib)
	{
		for (auto letter : text) {
			std::string let;
			let = letter;

			if (letter != ' ')
				AddSquare(position, { (float)fontSize, (float)fontSize }, color, spriteLib.Get(let));

			position.x += fontSize;
		}
	}




	void Renderer2D::AddSquare(Pro::Mat4 transform, Pro::Vec4 color)
	{
		AddSquare(transform, color, m_whiteSprite);
	}

	void Renderer2D::AddSquare(Pro::Mat4 transform, Pro::Vec4 color, Pro::Ref<Pro::Sprite>  sprite)
	{
		auto texture = sprite->GetSpriteSheet();
		int textureIndex = GetTextureIndex(texture);
		mesh.AddSquare(transform, color, textureIndex, sprite);
	}

	void Renderer2D::AddText(std::string text, Pro::Mat4 transform, Pro::Vec4 color, Pro::SpriteLibrary spriteLib)
	{
		for (auto letter : text) {
			std::string let;
			let = letter;

			if (letter != ' ')
				AddSquare(transform, color, spriteLib.Get(let));

			transform = Pro::Math::translate(transform, { 1, 0, 0 }); // Esto se mueve en una unidad en funcion del tamaño no en coordenadas globales

		}
	}



	int Renderer2D::GetTextureIndex(Pro::Ref<Pro::SpriteSheet>& texture)
	{
		m_textureCount = 0;
		for (auto text : m_textures)
		{

			if (text == texture)
			{
				return m_textureCount;
			}
			if (text == nullptr)
			{
				break;
			}
			m_textureCount++;
		}
		if (m_textureCount < 32) m_textures[m_textureCount] = texture;
		return m_textureCount;
	}

	bool Renderer2D::IsTextureBufferFilled()
	{
		return m_textureCount >= 32;
	}

	void Renderer2D::CleanTextureBuffer()
	{
		for (auto& text : m_textures) text = nullptr;
		m_textureCount = 0;
	}

	bool Renderer2D::IsTextureInBuffer(Pro::Ref<Pro::SpriteSheet>& texture)
	{
		for (auto text : m_textures)
		{
			if (text == texture) return true;
		}
		return false;
	}




}