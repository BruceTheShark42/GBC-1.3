#include "gbcpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace gbc
{
	static GLenum GetOpenGLUsage(BufferUsage usage)
	{
		switch (usage)
		{
			case BufferUsage::StreamDraw:  return GL_STREAM_DRAW;
			case BufferUsage::StreamRead:  return GL_STREAM_READ;
			case BufferUsage::StreamCopy:  return GL_STREAM_COPY;
			case BufferUsage::StaticDraw:  return GL_STATIC_DRAW;
			case BufferUsage::StaticRead:  return GL_STATIC_READ;
			case BufferUsage::StaticCopy:  return GL_STATIC_COPY;
			case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
			case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
			case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		}

		GBC_CORE_ASSERT(false, "Unknown Buffer Usage!");
		return 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, const void* data, BufferUsage usage)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GetOpenGLUsage(usage));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(uint32_t size, const void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, const void* data, BufferUsage usage, BufferIndexType type)
		: count(count), type(type)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<GLsizeiptr>(type), data, GetOpenGLUsage(usage));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(uint32_t count, const void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * static_cast<GLsizeiptr>(type), data);
	}
}
