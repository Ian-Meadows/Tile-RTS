#include "Chunk.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"
#include "ChunkGenerator.h"
#include "TextureAtlas.h"

Chunk::Chunk(glm::ivec2 position)
{
	this->position = position;

	ChunkGenerator::GenerateChunk(this);
	//init tiles
	tiles = new Tile**[CHUNK_SIZE];
	for (int x = 0; x < CHUNK_SIZE; x++) {
		tiles[x] = new Tile*[CHUNK_SIZE];
		for (int y = 0; y < CHUNK_SIZE; y++) {
			tiles[x][y] = new Tile(glm::ivec2(x + (CHUNK_SIZE * position.x), y + (CHUNK_SIZE * position.y)), chunkType);
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


glm::ivec2 Chunk::GetTileInfo(glm::ivec2 tilePos, TextureAtlas* ta) {
	return tiles[tilePos.x][tilePos.y]->GetUnitNumbers(ta);
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

bool Chunk::CheckForRenderUpdate() {
	return unrenderedUpdate;
}

void Chunk::Rendered() {
	unrenderedUpdate = false;
}


