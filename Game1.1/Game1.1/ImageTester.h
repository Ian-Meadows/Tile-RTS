#pragma once
#include "Shader.h"
class ImageTester
{
public:
	ImageTester();
	~ImageTester();

	void Update();
	void Draw();

private:
	unsigned int VAO, EBO;
	unsigned int VBO[2];
	unsigned int texture;
	Shader* shader;

	glm::vec3 position;
	unsigned int size;
	float rotation;

	glm::mat4 GetModel();

	void InitShape();
	void InitTexture();
};

