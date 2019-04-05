#include "TestRenderer.h"



TestRenderer::TestRenderer()
{

	shader = new Shader("TestVertexShader.vert", "TestFragmentShader.frag");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	float vert[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top  
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


TestRenderer::~TestRenderer()
{
	delete shader;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

}

void TestRenderer::Update() {

}

void TestRenderer::Draw() {
	shader->use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
