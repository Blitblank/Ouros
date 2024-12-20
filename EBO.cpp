
#include "EBO.hpp"

core::EBO::EBO(std::vector<GLuint>& indices) {
	glGenBuffers(1, &Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void core::EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void core::EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void core::EBO::Delete() {
	glDeleteBuffers(1, &Id);
}