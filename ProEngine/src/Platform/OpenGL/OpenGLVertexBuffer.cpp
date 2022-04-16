#include "Propch.h"
#include "OpenGLVertexBuffer.h"
#include "Platform/OpenGL/gl.h"

namespace Pro
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		PRO_PROFILE_FUNCTION();

		glGenBuffers(1, &m_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		PRO_PROFILE_FUNCTION();

		glGenBuffers(1, &m_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		PRO_PROFILE_FUNCTION();

	}

	void OpenGLVertexBuffer::Bind() const
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	}
	
	void OpenGLVertexBuffer::Unbind() const
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		PRO_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}