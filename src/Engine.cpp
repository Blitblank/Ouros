
#include "Engine.hpp"

#include<iostream>


#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Window.hpp"
#include "Texture.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

core::Engine::Engine() {
	std::cout << "Engine running..." << std::endl;
}

void core::Engine::run() {


	std::vector<Vertex> vertices = {
		Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 1.0f}}, // top right
		Vertex{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{1.0f, 0.0f}}, // bottom right
		Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 1.0f}}, // top left
		Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}}, // bottom left
		Vertex{glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{0.5f, 1.0f}}, // top middle
	};

	std::vector<unsigned int> indices = {
		//3, 1, 4,
		2, 0, 1,
		2, 1, 3
	};

	// geometry

	core::VAO vao;
	vao.Bind();

	core::VBO vbo(vertices);
	core::EBO ebo(indices);

	// Links VBO attributes such as coordinates and colors to VAO
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	//GLuint uniID = glGetUniformLocation(shader.Id, "scale");



	// texture 

	//Texture woodTexture("wood_plank.jpg", "AAAAA", 0);
	//Texture breakTexture("block_break.jpg", "AAAAA", 0);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../Assets/Textures/wood_plank.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: CANNOT LOAD TEXTURE" << std::endl;
	}


	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("../Assets/Textures/block_break.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: CANNOT LOAD TEXTURE" << std::endl;
	}

	stbi_image_free(data);

	shader.Activate();
	shader.set("texture1", 0);
	shader.set("texture2", 1);


	while (!glfwWindowShouldClose(window.getGLFWwindow())) {

		// input
		window.processInput(window.getGLFWwindow());

		// rendering commands 
		glClearColor(0.06f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();

		float timeValue = glfwGetTime();
		float r = (0.5f * sin(timeValue / 0.5f) + 0.5f);
		float g = (0.5f * sin(timeValue / 0.39f) + 0.5f);
		float b = (0.5f * sin(timeValue / 0.61f) + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shader.Id, "newColor");
		glUniform4f(vertexColorLocation, r, g, b, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		vao.Bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


		// check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getGLFWwindow());
	}

	glfwTerminate();


}

