#include "VitarPCH.h"
#include "Vitar/Core/Window.h"

#ifdef VITAR_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Vitar
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef VITAR_PLATFORM_WINDOWS
				return CreateScope<WindowsWindow>(props);
		#else
			VITAR_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
