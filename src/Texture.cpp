
#include "Texture.hpp"
#include <iostream>

core::Texture::Texture(std::string texturePath, GLenum textureType, GLuint slot, GLenum format, GLenum pixelType) {

		// assign texture type
		type = textureType;

		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true); // is upside down oherwise

		// read image from file
		std::string path = assetPath + texturePath;
		std::cout << path << std::endl;
		unsigned char* bytes = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);
		if(!bytes) {
			std::cout << "ERROR: CANNOT LOAD TEXTURE. ERR PATH: " << path << std::endl;
			return;
		}

		// bind texture
		glGenTextures(1, &Id);
		glActiveTexture(slot);
		glBindTexture(textureType, Id);
	
		// filtering
		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		// wrapping/repeating
		glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		// assign image
		glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes); 
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml for resources on format types (the type of data to be loaded: depth, rgb, rgba) and pixelTypes (float mostly here)
		// format is the pixel data from the image itself as its stored in the file. we use GL_RGBA in the internalFormat parameter to load it in a way that the shader uses
		// WARNING !!! pngs have an alpha channel whilke jpgs do not, so this will crash if format=GL_RGBA is used with a jpg (not the internal format, the shader auto truncates it)
		glGenerateMipmap(textureType);
	
		// unbind/clear memory
		stbi_image_free(bytes);
		glBindTexture(textureType, 0);

}

void core::Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.Id, uniform);
	shader.Activate();  // shader needs to be activated before changing the value of a uniform
	glUniform1i(texUni, unit); // set value

}

void core::Texture::Bind() {
	glBindTexture(type, Id);
}

void core::Texture::Unbind() {
	glBindTexture(type, 0);
}

void core::Texture::Delete() {
	glDeleteTextures(1, &Id);
}

