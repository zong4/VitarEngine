#pragma once

#include "Core.h"

namespace Vitar {

	class VITAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

