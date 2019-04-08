#include "Input.h"
#include <iostream>
#include <vector>


//only used once
namespace Input {
	//use for private methods and variables
	namespace {
		GLFWwindow* window;
		std::vector<int> keysPressed;
		std::vector<int> keysReleased;
		std::vector<int> keysHeld;


		void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
			
		}

		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				keysPressed.push_back(key);
				keysHeld.push_back(key);
			}
			else if (action == GLFW_RELEASE) {
				keysReleased.push_back(key);

				//TODO:Make faster
				for (int i = 0; i < keysHeld.size(); i++) {
					if (keysHeld[i] == key) {
						keysHeld.erase(keysHeld.begin() + i);
					}
				}
			}
		}

	}

	//put public mathods and variables here

	void Input::InitInput(GLFWwindow* window) {
		Input::window = window;
		//init callbacks
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetKeyCallback(window, KeyCallback);
	}


	void Input::ProcessInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	void Input::ClearOldInputs() {
		keysPressed.clear();
		keysReleased.clear();
	}

	bool GetKeyPressed(int key) {
		for (int i = 0; i < keysPressed.size(); i++) {
			if (key == keysPressed[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetKeyReleased(int key) {
		for (int i = 0; i < keysReleased.size(); i++) {
			if (key == keysReleased[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetKeyHeld(int key) {
		for (int i = 0; i < keysHeld.size(); i++) {
			if (key == keysHeld[i]) {
				return true;
			}
		}
		return false;
	}
}

