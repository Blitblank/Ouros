
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

		void updateTitle();

		int width; 
		int height;

	private:

		static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);
		void init();

		const std::string windowName;

		GLFWwindow* window;

		// variables for timetracking to display fps
		double prevTime = 0.0;
		double crntTime = 0.0;
		double timeDiff;
		unsigned int counter = 0;

	};


}