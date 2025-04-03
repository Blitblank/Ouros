
#pragma once

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

namespace core {

	struct Vertex {

		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texUV;
		
	};

	class VBO {

	public:

		VBO(std::vector<Vertex>& vertices);

		void Bind();
		void Unbind();
		void Delete();

	private:

		GLuint Id;

	};

}

