#pragma once
#include "Shader.h"

namespace UIHandler {
	void Init();
	void Draw();
	void Uninit();

	Shader* GetTextShader();
	Shader* GetShapeShader();

	glm::vec2 GetUpperLeft();
	glm::vec2 GetUpperRight();
	glm::vec2 GetLowerLeft();
	glm::vec2 GetLowerRight();
}

