#include "Chunk.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"


Chunk::Chunk(glm::ivec2 position)
{
	this->position = position;

	
	//init tiles
	tiles = new Tile**[CHUNK_SIZE];
	for (int x = 0; x < CHUNK_SIZE; x++) {
		tiles[x] = new Tile*[CHUNK_SIZE];
		for (int y = 0; y < CHUNK_SIZE; y++) {
			tiles[x][y] = nullptr;
		}
	}

}


Chunk::~Chunk()
{
	//delete tiles
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			if (tiles[x][y] != nullptr) {
				delete tiles[x][y];
			}
		}
		delete[] tiles[x];
	}
	delete[] tiles;
	
}

void Chunk::SemiGeneration() {
	gl = GenerationLevel::Semi;
}

void Chunk::FullGeneration() {
	gl = GenerationLevel::Full;
}


glm::ivec2 Chunk::GetPosition() {
	return position;
}


GenerationLevel Chunk::GetGenerationLevel() {
	return gl;
}


