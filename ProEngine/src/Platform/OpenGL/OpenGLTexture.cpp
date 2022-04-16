#include "Propch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"


namespace Pro
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_width(width), m_height(height)
	{
		PRO_PROFILE_FUNCTION();

		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_path(path)
	{
		PRO_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		m_width = width;
		m_height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_internalFormat = internalFormat;
		m_dataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		PRO_PROFILE_FUNCTION();
		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}


	void OpenGLTexture2D::SetSubData(void* data, uint32_t length, Vec2 pos, Vec2 size)
	{
		PRO_PROFILE_FUNCTION();
		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_textureID, 0, pos.x, pos.y, size.x, size.y, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		PRO_PROFILE_FUNCTION();
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		PRO_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_textureID);
	}

}