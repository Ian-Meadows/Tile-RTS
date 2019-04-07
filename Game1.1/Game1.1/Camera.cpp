#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"


namespace Camera {
	namespace {
		glm::mat4 view;

		glm::vec3 position;
		float rotation;

		void UpdateView() {
			view = glm::mat4(1.0f);
			view = glm::translate(view, position);
			view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	void Camera::Init() {
		position = glm::vec3(0, 0, -1);
		rotation = 0;
		UpdateView();
	}
	void Camera::Init(glm::vec3 position) {
		Camera::position = position;
		UpdateView();
	}
	void Camera::Init(glm::vec3 position, float rotation) {
		Camera::position = position;
		Camera::rotation = rotation;
		UpdateView();
	}
	void Camera::Init(float rotation) {
		Camera::rotation = rotation;
		UpdateView();
	}

	glm::mat4 Camera::GetView() {
		return view;
	}

	void Camera::SetPosition(glm::vec3 position) {
		Camera::position = position;
		UpdateView();
	}
	void Camera::SetRotation(float rotation) {
		Camera::rotation = rotation;
		UpdateView();
	}



	//do everything here
	void Camera::Update() {
		if (Input::GetKeyPressed(KeyCode::E)) {
			std::cout << "Pressed" << std::endl;
		}
		if (Input::GetKeyHeld(KeyCode::E)) {
			std::cout << "held" << std::endl;
		}
		if (Input::GetKeyReleased(KeyCode::E)) {
			std::cout << "Released" << std::endl;
		}
	}
}
