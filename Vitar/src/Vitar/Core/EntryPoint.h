#pragma once

#include "Vitar/Core/Base.h"
#include "Vitar/Core/Application.h"

#ifdef VITAR_PLANTFORM_WINDOWS

extern Vitar::Application* Vitar::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Vitar::Log::Init();

	VITAR_PROFILE_BEGIN_SESSION("Startup", "VitarProfiles-Startup.json");
	auto app = Vitar::CreateApplication({ argc, argv });
	VITAR_PROFILE_END_SESSION();

	VITAR_PROFILE_BEGIN_SESSION("Runtime", "VitarProfiles-Runtime.json");
	app->Run();
	VITAR_PROFILE_END_SESSION();

	VITAR_PROFILE_BEGIN_SESSION("Shutdown", "VitarProfiles-Shutdown.json");
	delete app;
	VITAR_PROFILE_END_SESSION();
}

#endif // VITAR_PLANTFORM_WINDOWS
