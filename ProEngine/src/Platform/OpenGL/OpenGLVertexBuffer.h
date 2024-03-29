#pragma once
#include "ProEngine/Renderer/VertexBuffer.h"

namespace Pro 
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; };

	private:
		uint32_t m_vertexBufferID;
		BufferLayout m_layout;
	};
}

