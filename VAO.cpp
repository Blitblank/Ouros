
#include "VAO.hpp"

core::VAO::VAO() {

	glGenVertexArrays(1, &Id);
}

void core::VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {

	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void core::VAO::Bind() {

	glBindVertexArray(Id);

}

void core::VAO::Unbind() {

	glBindVertexArray(0);
}

void core::VAO::Delete() {

	glDeleteVertexArrays(1, &Id);

}