#include "Propch.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/gl.h"

namespace Pro
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count)
		:m_count(count)
	{
		PRO_PROFILE_FUNCTION();

		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ARRAY_BUFFER, count, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_count(count)
	{
		PRO_PROFILE_FUNCTION();

		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		PRO_PROFILE_FUNCTION();

	}

	void OpenGLIndexBuffer::Bind() const 
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	}
	
	void OpenGLIndexBuffer::Unbind() const
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const void* data, uint32_t size)
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}
