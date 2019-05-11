#include "Input.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

//only used once
namespace Input {
	//use for private methods and variables
	namespace {
		GLFWwindow* window;
		std::vector<int> keysPressed;
		std::vector<int> keysReleased;
		std::vector<int> keysHeld;

		glm::vec2 scrollDelta;
		glm::vec2 mousePosition;

		void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
			mousePosition = glm::vec2(xpos, ypos);
		}

		void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
			scrollDelta = glm::vec2(xOffset, yOffset);
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

	//put public methods and variables here

	void Input::InitInput(GLFWwindow* window) {
		Input::window = window;
		scrollDelta = glm::vec2(0.0f, 0.0f);
		//init callbacks
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetScrollCallback(window, ScrollCallback);
	}


	void Input::ProcessInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	glm::vec2 Input::GetScrollDelta() {
		return scrollDelta;
	}
	glm::vec2 Input::GetMousePosition() {
		return mousePosition;
	}

	void Input::ClearOldInputs() {
		keysPressed.clear();
		keysReleased.clear();
		scrollDelta = glm::vec2(0.0f, 0.0f);
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

