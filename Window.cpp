
#include "Window.hpp"

#include<iostream>

core::Window::Window(int w, int h, std::string name) : width(w), height(h), windowName(name) {

	init();

}

core::Window::~Window() {

	glfwDestroyWindow(window);
	glfwTerminate();

}

void core::Window::frameBufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void core::Window::init() {

	// initializing glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// for displaying fullscreen on a specific monitor
	int monitorCount = 2;
	GLFWmonitor** monitor = glfwGetMonitors(&monitorCount);

	// where the magic happens (use minitor[0] instead of null for fullscreen)
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	//glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

	//gladLoadGL();
	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//glViewport(0, 0, width, height);

}

void core::Window::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}