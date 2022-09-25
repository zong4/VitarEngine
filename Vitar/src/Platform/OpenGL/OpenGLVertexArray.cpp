#include "VitarPCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Vitar
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Vitar::ShaderDataType::Float:     return GL_FLOAT;
		case Vitar::ShaderDataType::Float2:    return GL_FLOAT;
		case Vitar::ShaderDataType::Float3:    return GL_FLOAT;
		case Vitar::ShaderDataType::Float4:    return GL_FLOAT;
		case Vitar::ShaderDataType::Mat3:      return GL_FLOAT;
		case Vitar::ShaderDataType::Mat4:      return GL_FLOAT;
		case Vitar::ShaderDataType::Int:       return GL_INT;
		case Vitar::ShaderDataType::Int2:      return GL_INT;
		case Vitar::ShaderDataType::Int3:      return GL_INT;
		case Vitar::ShaderDataType::Int4:      return GL_INT;
		case Vitar::ShaderDataType::Bool:      return GL_BOOL;
		}

		VITAR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		VITAR_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		VITAR_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		VITAR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		VITAR_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		VITAR_PROFILE_FUNCTION();

		VITAR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		VITAR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
