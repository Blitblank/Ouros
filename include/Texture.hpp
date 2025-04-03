
#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "Shader.hpp"

namespace core {
	class Texture {
	public:

		Texture(std::string texturePath, GLenum textureType, GLuint slot, GLenum format, GLenum pixelType);
		~Texture() = default;

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

		GLuint Id;
		GLuint type;
		GLuint unit;

	private:

		const std::string assetPath = "../Assets/Textures/";

	};

}
