#pragma once

#include "Vitar/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <fstream>

// TODO 
typedef unsigned int GLenum;

namespace Vitar
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, const glm::vec2& value);
		void UploadUniformInt3(const std::string& name, const glm::vec3& value);
		void UploadUniformInt4(const std::string& name, const glm::vec4& value);

		void UploadUniformFloat1(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
	};
}