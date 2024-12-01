
#include "Shader.hpp"

#include<iostream>
#include<fstream>

// reads a text file (like our shader file) and returns the raw text
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	try
	{
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "ERROR: SHADER FILE CANNOT BE READ" << std::endl;
	}

}

// constructor builds the shader program
core::Shader::Shader(const char* vertexPath, const char* fragPath) {

	// read the vertex and frag files
	std::string vertexCode = get_file_contents(vertexPath);
	std::string fragCode = get_file_contents(fragPath);

	// conv to char*
	const char* vertexSource = vertexCode.c_str();
	const char* fragSource = fragCode.c_str();

	// create shader objects
	// vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");
	// frag
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");

	// create shader program
	Id = glCreateProgram();
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragShader);
	glLinkProgram(Id);
	compileErrors(Id, "PROGRAM");

	// delete shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

}

core::Shader::~Shader() {

}

void core::Shader::Activate() {
	glUseProgram(Id);
}

void core::Shader::Deactivate() {
	glDeleteProgram(Id);
}

void core::Shader::set(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
}

void core::Shader::set(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void core::Shader::set(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void core::Shader::compileErrors(unsigned int shader, const char* type) {

	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER " << type << " COMPILATION FAILED\n" << infoLog << std::endl;
		}
	}
	else {

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
		}
	}
}