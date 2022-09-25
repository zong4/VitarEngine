#include "VitarPCH.h"
#include <Vitar.h>
#include <Vitar/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Vitar::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Vitar::Application* Vitar::CreateApplication()
{
	return new Sandbox();
}