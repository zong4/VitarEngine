#include "VitarPCH.h"
#include <Vitar.h>

#include "imgui/imgui.h"

class ExampleLayer : public Vitar::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Vitar::VertexArray::Create());

		// Index Buffer, ÄæÊ±Õë
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};
		std::shared_ptr<Vitar::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Vitar::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vitar::BufferLayout layout = {
			{Vitar::ShaderDataType::Float3, "a_Position"},
			{Vitar::ShaderDataType::Float4, "a_Color"},
			//{ShaderDataType::Float3, "a_Normal"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Vitar::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Vitar::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Vitar::Shader(vertexSrc, fragmentSrc));
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

		Vitar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Vitar::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Vitar::Renderer::BeginScene(m_Camera);
		Vitar::Renderer::Submit(m_Shader, m_VertexArray);
		Vitar::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Vitar::Event& event) override
	{
		Vitar::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Vitar::KeyPressedEvent>(VITAR_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Vitar::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr<Vitar::Shader> m_Shader;
	std::shared_ptr<Vitar::VertexArray> m_VertexArray;

	// Examples
	std::shared_ptr<Vitar::Shader> m_BlueShader;
	std::shared_ptr<Vitar::VertexArray> m_SquareVA;

	Vitar::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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