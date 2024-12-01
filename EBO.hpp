
#pragma once

#include<vector>
#include<glad/glad.h>

namespace core {

	class EBO {

	public:

		EBO(std::vector<GLuint>& indices);
		~EBO() = default;

		void Bind();
		void Unbind();
		void Delete();

	private:

		GLuint Id;

	};


}