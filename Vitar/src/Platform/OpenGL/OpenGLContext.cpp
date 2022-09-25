#include "VitarPCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Vitar
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		VITAR_CORE_ASSERT(windowHandle, "Windows handle is null!");
	}

	void OpenGLContext::Init()
	{
		VITAR_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VITAR_CORE_ASSERT(status, "Failed to initalize Glad!");

		VITAR_CORE_INFO("OpenGL Info:");
		VITAR_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		VITAR_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		VITAR_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		VITAR_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}