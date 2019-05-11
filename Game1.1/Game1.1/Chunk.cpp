#include "Chunk.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"


Chunk::Chunk(glm::ivec2 position)
{
	this->position = position;

	
	cr = new ChunkRenderer(this);


}


Chunk::~Chunk()
{
	delete cr;
	/*
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(CHUNK_SIZE * CHUNK_SIZE, VBO);
	glDeleteBuffers(CHUNK_SIZE * CHUNK_SIZE, EBO);
	*/
}

glm::ivec2 Chunk::GetPosition() {
	return position;
}

void Chunk::Draw() {


	glm::mat4 model = glm::mat4(1.0f);
	
	model = glm::translate(model, glm::vec3(position.x, position.y, 0));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE));

	ChunkHandler::GetShader()->setMat4("model", model);

	/*
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize * (CHUNK_SIZE * CHUNK_SIZE), GL_UNSIGNED_INT, 0);
	*/
	cr->Draw();
}
