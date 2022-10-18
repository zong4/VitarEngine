#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"
#include "Camera.h"
#include "EditorCamera.h"

#include "Vitar/Scene/Components.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "UniformBuffer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Vitar
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		// Primitive
		static void DrawQuad(const glm::vec2& position = { 0.0f, 0.0f }, const glm::vec2& size = { 1.0f, 1.0f }, float rotation = 0.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f },
			const Ref<Texture2D>& texture = Texture2D::Create(1, 1, &(whiteTextureData), sizeof(uint32_t)), float tilingFactor = 1.0f, int entityID = -1);
		static void DrawQuad(const glm::vec3& position = { 0.0f,0.0f,0.0f }, const glm::vec2& size = { 1.0f, 1.0f }, float rotation = 0.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f },
			const Ref<Texture2D>& texture = Texture2D::Create(1, 1, &(whiteTextureData), sizeof(uint32_t)), float tilingFactor = 1.0f, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f), 
			const Ref<Texture2D>& texture = Texture2D::Create(1, 1, &(whiteTextureData), sizeof(uint32_t)), float tilingFactor = 1.0f, int entityID = -1);

		static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);

		static void DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, int entityID = -1);

		static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);

		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, float tilingFactor = 1.0f, int entityID = -1);

		static float GetLineWidth();
		static void SetLineWidth(float width);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static uint32_t whiteTextureData;

		static void StartBatch();
		static void NextBatch();
	};
}
