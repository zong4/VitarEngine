#pragma once

#ifdef VITAR_PLANTFORM_WINDOWS

extern Vitar::Application* Vitar::CreateApplication();

int main(int argc, char** argv)
{
	Vitar::Log::Init();
	VITAR_CORE_WARN("Initialized Log!");
	VITAR_INFO("Hello!");

	auto app = Vitar::CreateApplication();
	app->Run();
	delete app;
}

#endif // VITAR_PLANTFORM_WINDOWS
