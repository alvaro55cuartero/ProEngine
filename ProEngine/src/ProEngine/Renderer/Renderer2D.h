#pragma once
#include "ProEngine/Math/Vec3.h"
#include "ProEngine/Renderer/Sprite/Sprite.h"
#include "ProEngine/Renderer/Sprite/SpriteSheet.h"
#include "ProEngine/Renderer/Sprite/SpriteLibrary.h"
#include "ProEngine/Renderer/Mesh.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "ProEngine/Renderer/VertexArray.h"
#include "ProEngine/Renderer/RenderCommand.h"
#include "ProEngine/Math/Transform.h"
#include "ProEngine/Renderer/Cameras/Camera.h"


namespace Pro
{
	/*
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void BeginScene(const Camera& camera, const Mat4& transform);
		static void EndScene();
		static void Flush();


		static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color);
		static void DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color);
		static void DrawQuad(const Mat4& transform, const Vec4& color);
		static void DrawQuad(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));
		static void DrawQuad(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));

		static void DrawQuad(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, const Vec2& uvPos, const Vec2& uvSize, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));
		static void DrawQuad(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, const Vec2& uvPos, const Vec2& uvSize, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));

		static void DrawRotatedQuad(const Vec2& position, const Vec2& size, float rotation, const Vec4& color);
		static void DrawRotatedQuad(const Vec3& position, const Vec2& size, float rotation, const Vec4& color);
		static void DrawRotatedQuad(const Vec2& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));
		static void DrawRotatedQuad(const Vec3& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));

		static void DrawQuadImmediate(const Vec2& position, const Vec2& size, const Vec4& color);
		static void DrawQuadImmediate(const Vec3& position, const Vec2& size, const Vec4& color);
		static void DrawQuadImmediate(const Vec2& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));
		static void DrawQuadImmediate(const Vec3& position, const Vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));

		//static void DrawRotatedQuadImmediate(const Vec2& position, const Vec2& size, float rotation, const Vec4& color);
		//static void DrawRotatedQuadImmediate(const Vec3& position, const Vec2& size, float rotation, const Vec4& color);
		//static void DrawRotatedQuadImmediate(const Vec2& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));
		//static void DrawRotatedQuadImmediate(const Vec3& position, const Vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vec4& tintColor = Vec4(1.0f));

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();

	private:
		static void AddDataToBuffer(const Vec3& position, const Vec2& size,  const Vec4& color, float texIndex, float tilingFactor, const Vec2& uvPos = { 0,0 }, const Vec2& uvSize = { 1.0f, 1.0f });
		static void AddDataToBuffer(const Mat4& transform, const Vec4& color, float texIndex, float tilingFactor, const Vec2& uvPos = { 0,0 }, const Vec2& uvSize = { 1.0f, 1.0f });

		static void ResetBuffer();
	};
	*/

	class Renderer2D
	{

	public:
		Renderer2D() = default;

		void Init();
		void Render(const Camera & cam);



		void AddSquare(Vec3 Position, Vec2 size, Vec4 color, Ref<SpriteSheet>&texture);
		void AddSquare(Vec3 Position, Vec2 size, Vec4 color);
		void AddSquare(Vec3 Position, Vec2 size, Vec4 color, Ref<Sprite> sprite);

		void AddText(std::string text, Vec3 position, Vec4 color, int fontSize, SpriteLibrary spriteLib);


		void AddSquare(Mat4 transform, Vec4 color, Ref<Sprite> sprite, int textureIndex);
		void AddSquare(Mat4 transform, Vec4 color, Ref<Sprite> sprite);
		void AddSquare(Mat4 transform, Vec4 color);

		void AddText(std::string text, Mat4 transform, Vec4 color, SpriteLibrary spriteLib);


		int GetTextureIndex(Ref<SpriteSheet>&texture);
		bool IsTextureInBuffer(Ref<SpriteSheet>&texture);
		bool IsTextureBufferFilled();
		void CleanTextureBuffer();
	private:

		Mesh mesh;

		Ref<SpriteSheet> m_whiteTexture;

		Ref<Shader> m_shader;
		Ref<VertexArray> m_vao;
		Ref<VertexBuffer> m_vbo;
		Ref<IndexBuffer> m_ibo;

		Pro::Ref<Sprite> m_whiteSprite;

		std::array<Ref<SpriteSheet>, 32> m_textures;
		int m_texturesIndices[32] = {};

		Pro::Vec3 m_position;
		int m_SpriteCount = 0;
		int m_textureCount = 0;
		std::vector<float> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}