#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "ChunkHandler.h"
#include "Tile.h"

#define CHUNK_SIZE 32
#define UNIT_SIZE 1
/*
draw options
have vao for every chunk always in vram(lot of space)
init when going to draw(might be expensive to do)
*/
//lmao wat? the chunk doesn't even draw itsself anymore.


enum GenerationLevel { None, Semi, Full};

class Chunk
{
public:
	Chunk(glm::ivec2);
	~Chunk();
	

	glm::ivec2 GetPosition();

	void SemiGeneration();
	void FullGeneration();

	GenerationLevel GetGenerationLevel();

private:

	glm::ivec2 position;
	
	GenerationLevel gl = GenerationLevel::None;

	//2D with pointer to object
	Tile*** tiles;
};

