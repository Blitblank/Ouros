
#define STB_IMAGE_IMPLEMENTATION

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "Shader.hpp"

const char* assetPath = "Assets/Textures/";

namespace core {

	class Texture {
	public:

		Texture(const char* texturePath, const char* textureType, GLuint slot);
		~Texture() = default;

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

		GLuint Id;
		const char* type;
		GLuint unit;

	private:

	};

}