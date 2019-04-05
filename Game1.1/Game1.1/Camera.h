#pragma once
#include <glm/glm.hpp>

namespace Camera {
	void Init();
	void Init(glm::vec3);
	void Init(glm::vec3, float);
	void Init(float);

	glm::mat4 GetView();

	void SetPosition(glm::vec3);
	void SetRotation(float);

	void Update();
}

