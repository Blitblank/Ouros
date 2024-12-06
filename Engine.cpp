
#include "Engine.hpp"

#include<iostream>


#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Window.hpp"
#include "Texture.hpp"

core::Engine::Engine() {
	std::cout << "Engine running..." << std::endl;
}

void core::Engine::run() {


	float vertices[] = {
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, // top middle
	};

	unsigned int indices[] = {
		//3, 1, 4,
		2, 0, 1,
		2, 1, 3
	};


	// vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// element array buffer
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


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
	unsigned char* data = stbi_load("Assets/Textures/wood_plank.jpg", &width, &height, &nrChannels, 0);
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

	data = stbi_load("Assets/Textures/block_break.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: CANNOT LOAD TEXTURE" << std::endl;
	}

	stbi_image_free(data);

	shader.Activate();
	shader.set("texture2", 1);


	while (!glfwWindowShouldClose(window.getGLFWwindow())) {

		// input
		window.processInput(window.getGLFWwindow());

		// rendering commands 
		glClearColor(0.06f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();

		float timeValue = glfwGetTime();
		float g = (sin(timeValue / 2.0f) + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shader.Id, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, g, 0.0f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getGLFWwindow());
	}

	glfwTerminate();


}

