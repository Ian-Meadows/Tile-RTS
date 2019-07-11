#pragma once
#include "UIElement.h"
#include <glm/glm.hpp>

struct ShapeInput {
	float* vert;
	unsigned int vertSize;

	unsigned int* indi;
	unsigned int indiSize;

	const char* imagePath;

	ShapeInput(float* vert, unsigned int vertSize, unsigned int* indi, unsigned int indiSize, const char* imagePath) {
		this->vert = vert;
		this->vertSize = vertSize;

		this->indi = indi;
		this->indiSize = indiSize;

		this->imagePath = imagePath;
	}

	ShapeInput(float* vert, unsigned int vertSize, unsigned int* indi, unsigned int indiSize) {
		this->vert = vert;
		this->vertSize = vertSize;

		this->indi = indi;
		this->indiSize = indiSize;

		this->imagePath = "";
	}

	~ShapeInput() {

	}
};


class Shape
{
public:
	Shape(ShapeInput* input);
	~Shape();

	//Draws Shape, NOTE: must have a shader in use
	void Draw();

private:
	unsigned int VAO, VBO, EBO;

	unsigned int indiSize;

	void InitShape(ShapeInput* input);
};

