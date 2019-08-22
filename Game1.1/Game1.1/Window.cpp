#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"




#define MAXZOOM 2.0f
#define MINZOOM 0.01f

namespace Window {
	//use for private methods and variables
	namespace {
		int WIDTH, HEIGHT;
		//float SIZE = 0.25f;
		float SIZE = 0.01f;

		glm::mat4 perspective;

		void SetUpPerspective() {

			//perspective = glm::perspective(glm::radians(SIZE), ((float)XRESOLUTION / (float)YRESOLUTION), 0.1f, 1000.0f);

			//probably use this, might want to use the one below it though
			perspective = glm::ortho(-(XRESOLUTION / 2.0f * SIZE), XRESOLUTION / 2.0f * SIZE,
				-(YRESOLUTION / 2.0f * SIZE), YRESOLUTION / 2.0f * SIZE,
				0.1f, 10.0f);
			
			/*
			perspective = glm::ortho(-(WIDTH / 2.0f * SIZE), WIDTH / 2.0f * SIZE,
				-(HEIGHT / 2.0f * SIZE), HEIGHT / 2.0f * SIZE,
				0.1f, 100.0f);
			*/
		}

		void ZoomMovement() {
			glm::vec2 sd = Input::GetScrollDelta();
			if (sd.y != 0) {
				SIZE -= sd.y / 30.0f;
				if (SIZE < MINZOOM) {
					SIZE = MINZOOM;
				}
				else if (SIZE > MAXZOOM) {
					SIZE = MAXZOOM;
				}
				Window::SetUpPerspective();
			}
		}
	}

	//put public mathods and variables here
	void Window::InitWindow(int width, int height) {
		WIDTH = width;
		HEIGHT = height;

		Window::SetUpPerspective();
	}


	void Window::Update() {
		ZoomMovement();
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

