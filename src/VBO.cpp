
#include"VBO.hpp"

core::VBO::VBO(std::vector<Vertex>& vertices) {

	glGenBuffers(1, &Id);
	glBindBuffer(GL_ARRAY_BUFFER, Id);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void core::VBO::Bind() {

	glBindBuffer(GL_ARRAY_BUFFER, Id);

}

void core::VBO::Unbind() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void core::VBO::Delete() {

	glDeleteBuffers(1, &Id);

}