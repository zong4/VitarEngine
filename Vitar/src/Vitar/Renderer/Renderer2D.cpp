#include "VitarPCH.h"
#include "Renderer2D.h"

namespace Vitar
{
	//struct Renderer2DStorage
	//{
	//	Ref<VertexArray> VertexArray;
	//	Ref<Shader> TextureShader;
	//	Ref<Texture2D> WhiteTexture;
	//};

	//static Renderer2DStorage* s_Data;

	uint32_t Renderer2D::whiteTextureData = 0xffffffff;

	void Renderer2D::Init()
	{
		VITAR_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage;

		s_Data->VertexArray = VertexArray::Create();

		// Index Buffer, ÄæÊ±Õë
		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f,  1.0f,
		};

		Ref<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		m_VertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		});
		s_Data->VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[6] = { 0, 1, 2,
								2, 3, 0,};
		Ref<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		s_Data->VertexArray->SetIndexBuffer(m_IndexBuffer);

		// WhiteTexture
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
		
		// TextureShader
		s_Data->TextureShader = Shader::Create("src/assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		VITAR_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		VITAR_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		VITAR_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, float tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, float tilingFactor)
	{
		VITAR_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("v_Color", color);
		s_Data->TextureShader->SetFloat1("u_TilingFactor", tilingFactor);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
	}
}