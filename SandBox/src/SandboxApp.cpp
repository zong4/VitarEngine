#include "VitarPCH.h"
#include <Vitar.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Vitar::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f), m_TrianglePosition(0.0f)
	{
		m_VertexArray.reset(Vitar::VertexArray::Create());

		// Index Buffer, ÄæÊ±Õë
		float vertices[3 * 5] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f,
		};
		Vitar::Ref<Vitar::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Vitar::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vitar::BufferLayout layout = {
			{Vitar::ShaderDataType::Float3, "a_Position"},
			{Vitar::ShaderDataType::Float2, "a_TexCoord"},
			//{ShaderDataType::Float3, "a_Normal"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Vitar::Ref<Vitar::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Vitar::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//m_Shader.reset(Vitar::Shader::Create(vertexSrc, fragmentSrc));

		m_Shader.reset(Vitar::Shader::Create("src/assets/shaders/ShaderSource.glsl"));

		m_Texture2D = Vitar::Texture2D::Create("src/assets/textures/wolf.png");

		std::dynamic_pointer_cast<Vitar::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Vitar::Timestep timeStep) override
	{
		if (Vitar::Input::IsKeyPressed(VITAR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timeStep;
		else if (Vitar::Input::IsKeyPressed(VITAR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timeStep;
		
		if (Vitar::Input::IsKeyPressed(VITAR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timeStep;
		else if (Vitar::Input::IsKeyPressed(VITAR_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timeStep;

		if (Vitar::Input::IsKeyPressed(VITAR_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * timeStep;
		else if (Vitar::Input::IsKeyPressed(VITAR_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * timeStep;

		if (Vitar::Input::IsKeyPressed(VITAR_KEY_J))
			m_TrianglePosition.x -= m_TriangleMoveSpeed * timeStep;
		else if (Vitar::Input::IsKeyPressed(VITAR_KEY_L))
			m_TrianglePosition.x += m_TriangleMoveSpeed * timeStep;

		if (Vitar::Input::IsKeyPressed(VITAR_KEY_I))
			m_TrianglePosition.y += m_TriangleMoveSpeed * timeStep;
		else if (Vitar::Input::IsKeyPressed(VITAR_KEY_K))
			m_TrianglePosition.y -= m_TriangleMoveSpeed * timeStep;

		Vitar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Vitar::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Vitar::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<Vitar::OpenGLShader>(m_Shader)->UploadUniformFloat4("v_Color", m_Color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);
		m_Texture2D->Bind();

		Vitar::Renderer::Submit(m_Shader, m_VertexArray, transform);
		
		Vitar::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}

	void OnEvent(Vitar::Event& event) override
	{
	}

private:
	Vitar::Ref<Vitar::Shader> m_Shader;
	Vitar::Ref<Vitar::VertexArray> m_VertexArray;
	Vitar::Ref<Vitar::Texture2D> m_Texture2D;

	Vitar::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 5.0f;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };
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