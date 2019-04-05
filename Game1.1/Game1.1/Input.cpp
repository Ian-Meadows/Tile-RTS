#include "Input.h"
#include <iostream>


//only used once
namespace Input {
	//use for private methods and variables
	namespace {
		GLFWwindow* window;

		void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
			
		}

	}

	//put public mathods and variables here

	void Input::InitInput(GLFWwindow* window) {
		Input::window = window;
		//init callback
		glfwSetCursorPosCallback(window, MouseCallback);
	}


	void Input::ProcessInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
}

