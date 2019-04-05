#pragma once
#include <glm/glm.hpp>


namespace Window {
	void InitWindow(int, int);

	//getters
	int GetWidth();
	int GetHeight();
	int GetSize();
	glm::mat4 GetPerspective();

	//setters
	void ChangeSize(float);
	void ChangeSize(int, int);
	void ChangeSize(int, int , float);
}


