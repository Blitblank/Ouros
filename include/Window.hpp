
#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

namespace core {

	class Window {

	public:

		Window(int w, int h, std::string name);
		~Window();

		GLFWwindow* getGLFWwindow() const { return window; }

		void processInput(GLFWwindow* window);

	private:

		static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);
		void init();

		int width; 
		int height;
		const std::string windowName;

		GLFWwindow* window;

	};


}