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
};

