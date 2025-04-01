
#pragma once

#include<glad/glad.h>
#include "VBO.hpp"

namespace core {

	class VAO {

	public:

		VAO();
		~VAO() = default;

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();


	private:

		GLuint Id;

	};

}