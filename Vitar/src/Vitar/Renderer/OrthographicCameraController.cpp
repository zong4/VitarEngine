#include "VitarPCH.h"
#include "OrthographicCameraController.h"

#include "Vitar/Core/Input.h"
#include "Vitar/Core/KeyCodes.h"

Vitar::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
	: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
}

void Vitar::OrthographicCameraController::OnUpdate(Timestep timestep)
{
	VITAR_PROFILE_FUNCTION();

	if (Input::IsKeyPressed(Key::A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;
	else if (Input::IsKeyPressed(Key::D))
		m_CameraPosition.x += m_CameraTranslationSpeed * timestep;

	if (Input::IsKeyPressed(Key::S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;
	else if (Input::IsKeyPressed(Key::W))
		m_CameraPosition.y += m_CameraTranslationSpeed * timestep;

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(Key::Q))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		else if (Input::IsKeyPressed(Key::E))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;
}

void Vitar::OrthographicCameraController::OnEvent(Event& e)
{
	VITAR_PROFILE_FUNCTION();

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(VITAR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(VITAR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

void Vitar::OrthographicCameraController::OnResize(float width, float height)
{
	m_AspectRatio = width / height;
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

bool Vitar::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	VITAR_PROFILE_FUNCTION();

	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool Vitar::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	VITAR_PROFILE_FUNCTION();

	OnResize((float)e.GetWidth(), (float)e.GetHeight());
	return false;
}
