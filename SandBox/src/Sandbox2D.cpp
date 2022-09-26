#include "Sandbox2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	VITAR_PROFILE_FUNCTION();

	m_Texture2D = Vitar::Texture2D::Create("assets/textures/wolf.png");
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
	Vitar::Renderer2D::ResetStats();
	{
		VITAR_PROFILE_SCOPE("Renderer Prep");
		Vitar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Vitar::RenderCommand::Clear();
	}

	{
		VITAR_PROFILE_SCOPE("Renderer Draw");

		Vitar::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Vitar::Renderer2D::DrawQuad({ 1.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Vitar::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 45.0f, {1.0f, 1.0f, 1.0f, 0.5f}, m_Texture2D, 2.0f);

		Vitar::Renderer2D::EndScene();

		Vitar::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Vitar::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, 0.0f, color);
			}
		}

		Vitar::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	VITAR_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Vitar::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
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
