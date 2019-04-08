#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"
#include "Time.h"


#define MOVEMENT_SPEED 100


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

	void ChangePosition(glm::vec3 change) {
		Camera::position -= change;
		UpdateView();
	}



	//do everything here
	void Camera::Update() {
		if (Input::GetKeyHeld(KeyCode::W)) {
			ChangePosition(glm::vec3(0, MOVEMENT_SPEED * Time::GetDeltaTime(), 0));
		}
		else if (Input::GetKeyHeld(KeyCode::S)) {
			ChangePosition(glm::vec3(0, -MOVEMENT_SPEED * Time::GetDeltaTime(), 0));
		}

		if (Input::GetKeyHeld(KeyCode::A)) {
			ChangePosition(glm::vec3(-MOVEMENT_SPEED * Time::GetDeltaTime(), 0, 0));
		}
		else if (Input::GetKeyHeld(KeyCode::D)) {
			ChangePosition(glm::vec3(MOVEMENT_SPEED * Time::GetDeltaTime(), 0, 0));
		}
	}
}
