#include "TestRenderer.h"
#include "Window.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



TestRenderer::TestRenderer()
{

	shader = new Shader("Shaders/Vertex/TestVertexShader.vert", "Shaders/Fragment/TestFragmentShader.frag");
	
	InitShape();

	position = glm::vec3(0, 0, 0);
	size = 50;
	rotation = 0;

}

void TestRenderer::InitShape() {
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

glm::mat4 TestRenderer::GetModel() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, size, size));
	return model;
}

void TestRenderer::Draw() {
	shader->use();
	shader->setMat4("projection", Window::GetPerspective());
	shader->setMat4("view", Camera::GetView());
	shader->setMat4("model", GetModel());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
