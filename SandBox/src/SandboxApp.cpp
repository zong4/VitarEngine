#include "VitarPCH.h"
#include <Vitar.h>

#include "imgui/imgui.h"

class ExampleLayer : public Vitar::Layer
{
public:
	ExampleLayer() : Layer("Example") 
	{
	}

	void OnUpdate() override
	{
		if (Vitar::Input::IsKeyPressed(VITAR_KEY_TAB))
			VITAR_INFO("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World!");
		//ImGui::End();
	}

	void OnEvent(Vitar::Event& event) override
	{
		if (event.GetEventType() == Vitar::EventType::KeyPressed)
		{
			Vitar::KeyPressedEvent& e = (Vitar::KeyPressedEvent&)event;
			VITAR_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Vitar::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Vitar::Application* Vitar::CreateApplication()
{
	return new Sandbox();
}