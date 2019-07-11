#pragma once
#include <glm/glm.hpp>

#define XRESOLUTION 800
#define YRESOLUTION 600

namespace Window {
	void InitWindow(int, int);

	void Update();

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


