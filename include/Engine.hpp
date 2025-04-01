#pragma once

#include "Shader.hpp"
#include "Window.hpp"

namespace core {

	class Engine {

	public:

		Engine();
		~Engine() = default;

		void run();

		static const int WIDTH = 800;
		static const int HEIGHT = 600;

	private:

		Window window{ WIDTH, HEIGHT, "Ouros" };

		Shader shader{ "../src/shaders/basic.vert", "../src/shaders/basic.frag" };

	};

}