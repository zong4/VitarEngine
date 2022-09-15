#include <Vitar.h>

class Sandbox : public Vitar::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Vitar::Application* Vitar::CreateApplication()
{
	return new Sandbox();
}