#include "Propch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/gl.h"

namespace Pro
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::UByte:		return GL_UNSIGNED_BYTE;
		case ShaderDataType::UByte4:	return GL_UNSIGNED_BYTE;
		}

		return 0;
	}



	OpenGLVertexArray::OpenGLVertexArray()
	{
		PRO_PROFILE_FUNCTION();

		glGenVertexArrays(1, &m_vertexArrayID);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		PRO_PROFILE_FUNCTION();

	}

	void OpenGLVertexArray::Bind() const
	{
		PRO_PROFILE_FUNCTION();

		glBindVertexArray(m_vertexArrayID);
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		PRO_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		PRO_PROFILE_FUNCTION();

		glBindVertexArray(m_vertexArrayID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			case ShaderDataType::UByte:
			case ShaderDataType::UByte4:
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribPointer(m_vertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
				m_vertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribPointer(m_vertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(sizeof(float) * count * i));
					//glVertexAttribDivisor(m_vertexBufferIndex, 1);
					m_vertexBufferIndex++;
				}
				break;
			}
			}
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}


	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		PRO_PROFILE_FUNCTION();

		glBindVertexArray(m_vertexArrayID);
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;
	}
}