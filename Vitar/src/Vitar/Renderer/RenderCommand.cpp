#include "VitarPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Vitar
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}