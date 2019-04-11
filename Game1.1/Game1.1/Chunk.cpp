#include "Chunk.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"


Chunk::Chunk(glm::ivec2 position)
{
	this->position = position;

	/*
	float vert[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indi[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	

	unsigned int indi[] = {
				0, 1, 3,
				1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(CHUNK_SIZE * CHUNK_SIZE, VBO);
	glGenBuffers(CHUNK_SIZE * CHUNK_SIZE, EBO);

	glBindVertexArray(VAO);
	int i = 0;
	for (float x = 0; x < CHUNK_SIZE; x++) {
		for (float y = 0; y < CHUNK_SIZE; y++) {
			i++;
			float vert[] = {
				x + 1, y + 1, 0.0f,
				x + 1, y, 0.0f,
				x, y, 0.0f,
				x, y + 1, 0.0f
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);
		}
	}

	indicesSize = 6;

	

	
	//glGenBuffers(1, &VBO);
	

	


	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/
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
