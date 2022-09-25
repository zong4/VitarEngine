#include "Sandbox2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	VITAR_PROFILE_FUNCTION();

	m_Texture2D = Vitar::Texture2D::Create("src/assets/textures/wolf.png");
}

void Sandbox2D::OnDetach()
{
	VITAR_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Vitar::Timestep timestep)
{
	VITAR_PROFILE_FUNCTION();

	// Update
	{
		VITAR_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	// Render
	{
		VITAR_PROFILE_SCOPE("Renderer Prep");
		Vitar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Vitar::RenderCommand::Clear();
	}

	{
		VITAR_PROFILE_SCOPE("Renderer Draw");
		Vitar::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Vitar::Renderer2D::DrawQuad({ 1.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, 0.0f, { 0.8f, 0.2f, 0.3f, 1.0f });

		Vitar::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, {1.0f, 1.0f, 1.0f, 0.5f}, m_Texture2D);

		Vitar::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));

	ImGui::End();
}

void Sandbox2D::OnEvent(Vitar::Event& event)
{
	m_CameraController.OnEvent(event);

	if (event.GetEventType() == Vitar::EventType::WindowResize)
	{
		//auto& resizeEvent = (Vitar::WindowResizeEvent&)event;
		//m_CameraController.SetZoomLevel((float)resizeEvent.GetWidth() / 1280.0f);
	}
}
