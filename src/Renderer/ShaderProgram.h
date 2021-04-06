#pragma once
#include <string>
#include <glad/glad.h>

namespace Renderer
{

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
		~ShaderProgram();
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		bool isCompiled() const { return this->m_isCompiled; }
		void use() const;

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};

}

