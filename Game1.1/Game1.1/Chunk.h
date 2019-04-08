#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "ChunkHandler.h"

#define CHUNK_SIZE 5
#define UNIT_SIZE 20
/*
draw options
have vao for every chunk always in vram(lot of space)
init when going to draw(might be expensive to do)
*/


class Chunk
{
public:
	Chunk(glm::ivec2);
	~Chunk();
	void Draw();

private:
	glm::ivec2 position;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	GLsizei indicesSize;

};

