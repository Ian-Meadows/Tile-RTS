#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"
#include "Time.h"
#include "Window.h"
#include "Chunk.h"


#define MOVEMENT_SPEED 100
#define MINZOOM -25
#define MAXZOOM -1000

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

	glm::vec3 Camera::GetPosition() {
		return position;
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
		CameraMovement();
		//ZoomMovement();
	}

	void Camera::CameraMovement() {
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

	void Camera::ZoomMovement() {
		glm::vec2 sd = Input::GetScrollDelta();
		if (sd.y != 0) {
			Camera::position.z += sd.y * 10;
			if (Camera::position.z > MINZOOM) {
				Camera::position.z = MINZOOM;
			}
			else if (Camera::position.z < MAXZOOM) {
				Camera::position.z = MAXZOOM;
			}
			UpdateView();
		}
	}

	//util Functions
	glm::vec3 Camera::ScreenToWorld(glm::vec2 pos) {
		int width = Window::GetWidth();
		int height = Window::GetHeight();

		glm::mat4 proj = Window::GetPerspective() * view;

		glm::vec4 viewport = glm::vec4(0, height, width, -height);
		
		glm::vec3 worldPos = glm::unProject(glm::vec3(pos.x, pos.y, 0.0f), glm::mat4(1.0f), proj, viewport);

		//change worldPos to match chunk/unit alignment
		worldPos.x += UNIT_SIZE / 2.0f;
		worldPos.y += UNIT_SIZE / 2.0f;
		return worldPos;
	}


}
