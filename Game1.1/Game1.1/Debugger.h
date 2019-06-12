#pragma once
#include <glm/glm.hpp>


namespace Debugger {
	void PrintVector(glm::vec1 vector);
	void PrintVector(glm::vec2 vector);
	void PrintVector(glm::vec3 vector);
	void PrintVector(glm::vec4 vector);

	void PrintVector(glm::vec1 vector, const char* message);
	void PrintVector(glm::vec2 vector, const char* message);
	void PrintVector(glm::vec3 vector, const char* message);
	void PrintVector(glm::vec4 vector, const char* message);
}

