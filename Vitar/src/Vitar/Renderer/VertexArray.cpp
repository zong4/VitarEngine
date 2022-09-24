#include "VitarPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Vitar
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      VITAR_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLVertexArray>();
		}

		VITAR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}