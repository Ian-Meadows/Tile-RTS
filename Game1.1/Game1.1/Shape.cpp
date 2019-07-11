#include "Shape.h"
#include <glad/glad.h>
#include <iostream>


Shape::Shape(ShapeInput* input)
{
	indiSize = input->indiSize;
	InitShape(input);

	std::cout << "hi" << std::endl;
}


Shape::~Shape()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Shape::InitShape(ShapeInput* input) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, input->vertSize, input->vert, GL_STATIC_DRAW);

	//std::cout << sizeof(input->indi) << std::endl;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, input->indiSize * 4, input->indi, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	delete input;
}

void Shape::Draw() {


	//bind vao
	glBindVertexArray(VAO);
	//render shape
	glDrawElements(GL_TRIANGLES, indiSize, GL_UNSIGNED_INT, 0);
}

