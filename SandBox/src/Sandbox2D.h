#pragma once

#include "VitarPCH.h"
#include <Vitar.h>

#include "imgui/imgui.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Vitar::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Vitar::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Vitar::Event& event) override;

private:
	Vitar::OrthographicCameraController m_CameraController;

	// TEMPORARY
	Vitar::ShaderLibrary m_ShaderLibrary;
	Vitar::Ref<Vitar::Shader> m_Shader;
	Vitar::Ref<Vitar::VertexArray> m_VertexArray;
	Vitar::Ref<Vitar::Texture2D> m_Texture2D;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };
};