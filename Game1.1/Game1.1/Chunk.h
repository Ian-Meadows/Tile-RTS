#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "ChunkHandler.h"

#define CHUNK_SIZE 32
#define UNIT_SIZE 1
/*
draw options
have vao for every chunk always in vram(lot of space)
init when going to draw(might be expensive to do)
*/
//lmao wat? the chunk doesn't even draw itsself anymore.


class Chunk
{
public:
	Chunk(glm::ivec2);
	~Chunk();
	//void Draw();

	glm::ivec2 GetPosition();

private:

	glm::ivec2 position;
	/*
	unsigned int VAO;
	unsigned int VBO[CHUNK_SIZE * CHUNK_SIZE];
	unsigned int EBO[CHUNK_SIZE * CHUNK_SIZE];

	GLsizei indicesSize;
	*/
};

