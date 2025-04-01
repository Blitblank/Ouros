
#pragma once

#include<glad/glad.h>

#include<string>

namespace core {

	class Shader {

	public:

		Shader(const char* vertexPath, const char* fragPath);
		~Shader();

		void Activate();
		void Deactivate();

		void set(const std::string& name, bool value) const;
		void set(const std::string& name, int value) const;
		void set(const std::string& name, float value) const;

		GLuint Id;

	private:

		void compileErrors(unsigned int shader, const char* type);

	};

}