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

	//0:shape
	//1:texcoords
	unsigned int VBO[2];
	unsigned int texture;
	Shader* shader;

	glm::vec3 position;
	unsigned int size;
	float rotation;

	int unitNum = 0;
	double t = 0;

	glm::mat4 GetModel();

	void InitShape();
	void InitTexture();
};

