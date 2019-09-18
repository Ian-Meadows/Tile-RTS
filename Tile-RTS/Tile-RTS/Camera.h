#pragma once
#include <glm/glm.hpp>

namespace Camera {
	void Init();
	void Init(glm::vec3);
	void Init(glm::vec3, float);
	void Init(float);

	glm::mat4 GetView();
	glm::vec3 GetPosition();

	void SetPosition(glm::vec3);
	void SetRotation(float);

	void Update();

	void CameraMovement();
	void ZoomMovement();

	void ChangePosition(glm::vec3);

	glm::vec3 ScreenToWorld(glm::vec2 pos);
}

