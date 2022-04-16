#pragma once
#include "ProEngine/Renderer/Texture.h"
#include "Platform/OpenGL/gl.h"


namespace Pro 
{
	class OpenGLTexture2D : public Texture2D
	{

	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_width; }
		virtual uint32_t GetHeight() const override { return m_height; }
		virtual uint32_t GetNativeID() const override { return m_textureID; }

		virtual void SetData(void* data, uint32_t size) override;
		virtual void SetSubData(void* data, uint32_t length, Vec2 pos, Vec2 size) override;

		virtual void Bind(uint32_t slot = 0) const override;


		virtual bool operator==(const Texture& other) const override
		{
			return m_textureID == ((OpenGLTexture2D&)other).m_textureID;
		}

	private:
		std::string m_path;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_textureID;
		GLenum m_internalFormat;
		GLenum	m_dataFormat;
	};

}