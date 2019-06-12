#include "Debugger.h"
#include <iostream>

namespace Debugger {
	namespace {

	}

	void PrintVector(glm::vec1 vector) {
		std::cout << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::vec2 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::vec3 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::vec4 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}


	void PrintVector(glm::vec1 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::vec2 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::vec3 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::vec4 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}
}
