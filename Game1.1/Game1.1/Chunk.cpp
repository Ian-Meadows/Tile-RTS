#include "Chunk.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time.h"
#include "ChunkGenerator.h"
#include "TextureAtlas.h"
#include "ChunkRenderer.h"

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


//Takes local Coords and non null unit(does not check if null). Places unit in position if possible
bool Chunk::PlaceUnit(glm::ivec2 position, Unit* unit) {
	if (OutOfRange(position)) {
		return false;
	}

	if (tiles[position.x][position.y]->unit == nullptr) {
		tiles[position.x][position.y]->unit = unit;
		if (cr != nullptr && cr->GetChunk() == this) {
			cr->UpdateSingleUnitRender(position, tiles[position.x][position.y]->GetUnitNumbers(ChunkHandler::GetTextureAtlas()));

			
		}
		return true;
	}
	else {
		return false;
	}

}

//Takes local Coords. Returns unit at coords
Unit* Chunk::GetUnit(glm::ivec2 position) {
	if (OutOfRange(position)) {
		return nullptr;
	}

	return tiles[position.x][position.y]->unit;
}

//Takes local Coords. Sets unit to null
void Chunk::ClearUnit(glm::ivec2 position) {
	if (OutOfRange(position)) {
		return;
	}

	tiles[position.x][position.y]->unit = nullptr;
	if (cr != nullptr && cr->GetChunk() == this) {
		cr->UpdateSingleUnitRender(position, tiles[position.x][position.y]->GetUnitNumbers(ChunkHandler::GetTextureAtlas()));
	}
	
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

void Chunk::SetChunkRenderer(ChunkRenderer* cr) {
	this->cr = cr;
}

bool Chunk::OutOfRange(glm::ivec2 coords) {
	if (coords.x < 0 || coords.y < 0 || coords.x >= CHUNK_SIZE || coords.y >= CHUNK_SIZE) {
		return true;
	}
	return false;
}



