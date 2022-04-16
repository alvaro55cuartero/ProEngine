#pragma once
#include "ProEngine/Renderer/IndexBuffer.h"

namespace Pro
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		OpenGLIndexBuffer(uint32_t count);



		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetData(const void* data, uint32_t size);

		virtual uint32_t GetCount() const { return m_count; }
	private:
		uint32_t m_indexBufferID;
		uint32_t m_count;
	};
}