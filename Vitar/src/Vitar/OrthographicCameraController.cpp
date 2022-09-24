#include "VitarPCH.h"
#include "OrthographicCameraController.h"

#include "Vitar/Input.h"
#include "Vitar/KeyCodes.h"

Vitar::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
	: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
}

void Vitar::OrthographicCameraController::OnUpdate(Timestep timestep)
{
	if (Input::IsKeyPressed(VITAR_KEY_A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;
	else if (Input::IsKeyPressed(VITAR_KEY_D))
		m_CameraPosition.x += m_CameraTranslationSpeed * timestep;

	if (Input::IsKeyPressed(VITAR_KEY_S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;
	else if (Input::IsKeyPressed(VITAR_KEY_W))
		m_CameraPosition.y += m_CameraTranslationSpeed * timestep;

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(VITAR_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		else if (Input::IsKeyPressed(VITAR_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;
}

void Vitar::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(VITAR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(VITAR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool Vitar::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool Vitar::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}