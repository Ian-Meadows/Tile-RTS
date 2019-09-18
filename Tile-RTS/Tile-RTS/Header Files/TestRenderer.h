#pragma once
#include "Shader.h"
class TestRenderer
{
public:
	TestRenderer();
	~TestRenderer();

	void Update();
	void Draw();

private:

	Shader* shader;
	
	unsigned int VAO;
	unsigned int VBO;

	glm::vec3 position;
	unsigned int size;
	float rotation;

	glm::mat4 GetModel();

	void InitShape();

};

