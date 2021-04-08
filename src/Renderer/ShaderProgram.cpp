#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader)
	{
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		bool vsIsCompiled = createShader(vertex_shader, GL_VERTEX_SHADER, vertexShaderID);
		bool fsIsCompiled = createShader(fragment_shader, GL_FRAGMENT_SHADER, fragmentShaderID);

		if (!vsIsCompiled)
		{
			std::cerr << "Vertex shader is not compiled" << std::endl;
			return;
		}

		if (!fsIsCompiled)
		{
			std::cerr << "Fragment shader is not compiled" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_PROGRAM, &success);

		if (!success)
		{
			GLchar infoLog[1024];
			glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);

			std::cerr << "ERROR::SHADER: link time error: \n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);

			std::cerr << "ERROR::SHADER: Compile time error: \n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = NULL;
		shaderProgram.m_isCompiled = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = NULL;
		shaderProgram.m_isCompiled = false;

	}

	void ShaderProgram::setInt(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}
}