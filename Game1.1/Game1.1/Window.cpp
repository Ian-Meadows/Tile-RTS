#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Window {
	//use for private methods and variables
	namespace {
		int WIDTH, HEIGHT;
		float SIZE = 1;

		glm::mat4 perspective;

		void SetUpPerspective() {
			perspective = glm::ortho(-(WIDTH / 2.0f * SIZE), WIDTH / 2.0f * SIZE,
				-(HEIGHT / 2.0f * SIZE), HEIGHT / 2.0f * SIZE,
				0.1f, 100.0f);
		}
	}

	//put public mathods and variables here
	void Window::InitWindow(int width, int height) {
		WIDTH = width;
		HEIGHT = height;

		Window::SetUpPerspective();
	}


	//getters
	int Window::GetWidth() {
		return WIDTH;
	}
	int Window::GetHeight() {
		return HEIGHT;
	}
	int Window::GetSize() {
		return SIZE;
	}
	glm::mat4 Window::GetPerspective() {
		return perspective;
	}

	//setters
	void Window::ChangeSize(float size) {
		SIZE = size;
		Window::SetUpPerspective();
	}
	void Window::ChangeSize(int width, int height) {
		WIDTH = width;
		HEIGHT = height;
		Window::SetUpPerspective();
	}
	void Window::ChangeSize(int width, int height, float size) {
		WIDTH = width;
		HEIGHT = height;
		SIZE = size;
		Window::SetUpPerspective();
	}
}

