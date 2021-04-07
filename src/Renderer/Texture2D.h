#pragma once
#include<glad/glad.h>
#include <string>



namespace Renderer
{

	class Texture2D
	{
	public:
		Texture2D(const GLuint width, const GLuint height,
				  const unsigned char* data,
				  const unsigned int channels,
				  const GLenum filter,
				  const GLenum wrapMode);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2D);
		Texture2D(Texture2D&& texture2D);

		void bind() const;

		~Texture2D();
	private:
		GLuint m_ID;
		unsigned int m_width;
		unsigned int m_height;
		GLenum m_mode;
	};
}
