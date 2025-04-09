
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Engine.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

core::Engine::Engine() {
	std::cout << "Engine running..." << std::endl;
}

void core::Engine::run() {

	// hard coded geometry. to be moved into a mesh class then moved into a model class
	std::vector<Vertex> vertices = {
		Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{0.2f, 0.3f}}, // top right
		Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.8f, 0.3f}}, // bottom right
		Vertex{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.2f, 0.3f}}, // top left
		Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec2{0.8f, 0.3f}}, // bottom left
		Vertex{glm::vec3{0.0f, 0.0f, 0.8f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{0.5f, 0.9f}}, // top middle
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
	};

	// geometry binding. each object is unique to each model/mesh
	core::VAO vao; // vertex array object 
	vao.Bind(); // organizes vertex data into the array vvvv see below

	core::VBO vbo(vertices); // vertex buffer object
	core::EBO ebo(indices); // element buffer object

	// links attributes from the vbo to the vao. all the numbers are for organizing the data into a single stream
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// unbind for memory saftey
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	//GLuint uniID = glGetUniformLocation(shader.Id, "scale");

	// texture 
	Texture woodTexture("obamna.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	woodTexture.texUnit(shader, "tex0", 0);
	Texture breakTexture("block_break.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
	breakTexture.texUnit(shader, "tex1", 0);

	// link shader values. shder.set(x) allows variable x to be used in the shader
	shader.Activate();
	shader.set("texture1", 0);
	shader.set("texture2", 1);

	glEnable(GL_DEPTH_TEST);

	// update loop. (might move this later)
	while (!glfwWindowShouldClose(window.getGLFWwindow())) {

		window.updateTitle();

		// input
		window.processInput(window.getGLFWwindow());
		// todo input system

		// rendering commands 
		glClearColor(0.06f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		// init matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		// assign matrices
		model = glm::rotate(model, float(glm::radians(glfwGetTime()*200.0)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(glfwGetTime()*5.0f)*0.15));
		view = glm::translate(view, glm::vec3(0.0f, -2.0f, -0.5f));
		proj = glm::perspective(glm::radians(45.0f), (float)window.width / window.height, 0.1f, 100.0f);
		proj = glm::rotate(proj, float(glm::radians(90.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
		proj = glm::rotate(proj, float(glm::radians(180.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		// send matrices to vertex shader
		int modelLoc = glGetUniformLocation(shader.Id, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.Id, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shader.Id, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		float timeValue = glfwGetTime();
		float r = (0.5f * sin(timeValue / 0.5f) + 0.5f);
		float g = (0.5f * sin(timeValue / 0.39f) + 0.5f);
		float b = (0.5f * sin(timeValue / 0.61f) + 0.5f);
		unsigned int vertexColorLocation = glGetUniformLocation(shader.Id, "newColor");
		glUniform4f(vertexColorLocation, r, g, b, 1.0f);

		// only binds to active texture, have to specify which to bind to
		glActiveTexture(GL_TEXTURE0);
		woodTexture.Bind();
		glActiveTexture(GL_TEXTURE1);
		breakTexture.Bind();

		// activate all the vertex data
		vao.Bind();

		// draw that baybee !!
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


		// check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.getGLFWwindow());
	}

	glfwTerminate();


}

