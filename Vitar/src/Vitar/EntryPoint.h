#pragma once

#ifdef VITAR_PLANTFORM_WINDOWS

extern Vitar::Application* Vitar::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Vitar Engine" << std::endl;
	auto app = Vitar::CreateApplication();
	app->Run();
	delete app;
}

#endif // VITAR_PLANTFORM_WINDOWS
