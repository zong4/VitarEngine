#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vitar
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitive
		static void DrawQuad(const glm::vec2& position = { 0.0f, 0.0f }, const glm::vec2& size = { 1.0f, 1.0f }, float rotation = 0.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f },
			const Ref<Texture2D>& texture = Texture2D::Create(1, 1, &(whiteTextureData), sizeof(uint32_t)), float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position = { 0.0f,0.0f,0.0f }, const glm::vec2& size = { 1.0f, 1.0f }, float rotation = 0.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f },
			const Ref<Texture2D>& texture = Texture2D::Create(1, 1, &(whiteTextureData), sizeof(uint32_t)), float tilingFactor = 1.0f);
	
		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static uint32_t whiteTextureData;

		static void FlushAndReset();
	};
}