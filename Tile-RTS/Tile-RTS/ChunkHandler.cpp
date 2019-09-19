#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <math.h>

#include "Camera.h"
#include "Window.h"
#include "TextureAtlasCreator.h"
#include "Chunk.h"
#include "Unit.h"
#include "Debugger.h"
#include "Tile.h"

#include "stb_image.h"


namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;

		glm::ivec2 worldSize;

		Chunk* CreateNewChunk(glm::ivec2 pos) {
			if (worldSize == INFINITE_WORLD ||
				(worldSize.x >= abs(pos.x) && worldSize.y >= abs(pos.y))) {
				Chunk* c = new Chunk(pos);
				chunksList.push_back(c);
				chunks[pos] = c;
				return c;
			}
			else {
				return nullptr;
			}
		}

		TextureAtlas* ta;
		
	}

	void ChunkHandler::Init(glm::ivec2 worldSize, bool fullyLoadWorld) {
		
		ChunkHandler::worldSize = worldSize;

		ta = TextureAtlasCreator::GetAtlas(false);

		if (fullyLoadWorld && worldSize != INFINITE_WORLD) {
			for (int x = -worldSize.x; x <= worldSize.x; ++x) {
				for (int y = -worldSize.y; y <= worldSize.y; ++y) {
					CreateNewChunk(glm::ivec2(x, y));
				}
			}
		}
	}

	void ChunkHandler::Uninit() {
		chunks.clear();
		for (unsigned int i = 0; i < chunksList.size(); i++) {
			delete chunksList[i];
		}
		chunksList.clear();
	}

	TextureAtlas* GetTextureAtlas() {
		return ta;
	}

	//TODO::add chunk generation
	Chunk* ChunkHandler::GetChunk(glm::ivec2 pos) {
		Chunk* c = chunks[pos];
		if (c == nullptr) {
			c = CreateNewChunk(pos);
			return c;
		}
		else {
			return c;
		}
		
	}


	bool ChunkHandler::MoveUnit(glm::ivec2 startPosition, glm::ivec2 endPosition) {
		//step 1: get coords first
		//step 2: check if its possible to move
		//step 3: move unit

		glm::ivec2 startChunkPos = glm::ivec2(floor(startPosition.x / (float)CHUNK_SIZE), floor(startPosition.y / (float)CHUNK_SIZE));
		glm::ivec2 endChunkPos = glm::ivec2(floor(endPosition.x / (float)CHUNK_SIZE), floor(endPosition.y / (float)CHUNK_SIZE));


		Chunk* startChunk;
		Chunk* endChunk;
		if (startChunkPos == endChunkPos) {
			startChunk = GetChunk(startChunkPos);
			endChunk = startChunk;
		}
		else {
			startChunk = GetChunk(startChunkPos);
			endChunk = GetChunk(endChunkPos);
		}
		if (startChunk == nullptr || endChunk == nullptr) {
			return false;
		}

		glm::ivec2 localStartPos = startPosition - (startChunkPos * CHUNK_SIZE);
		glm::ivec2 localEndPos = endPosition - (endChunkPos * CHUNK_SIZE);

		if (endChunk->GetUnit(localEndPos) != nullptr) {
			//unable to move unit location is occupied
			std::cout << "Unable to move unit location is occupied" << std::endl;
			return false;
		}

		Unit* unitToMove = startChunk->GetUnit(localStartPos);
		if (unitToMove == nullptr || !unitToMove->IsMovable()) {
			//unit does not exist or is immobile
			std::cout << "Unable to move unit" << std::endl;
			return false;
		}

		

		//move
		if (!endChunk->PlaceUnit(localEndPos, unitToMove)) {
			return false;
		}
		//clear old location
		startChunk->ClearUnit(localStartPos);

		return true;
	}

	bool ChunkHandler::PlaceUnit(glm::ivec2 position, Unit* unit) {
		//get chunk coords
		glm::ivec2 chunkPos = glm::ivec2(floor(position.x / (float)CHUNK_SIZE), floor(position.y / (float)CHUNK_SIZE));

		//get chunk at coords
		Chunk* chunk = GetChunk(chunkPos);

		if (chunk == nullptr) {
			return false;
		}

		//get local coords
		glm::ivec2 localCoords = position - (chunkPos * CHUNK_SIZE);

		//place unit
		return chunk->PlaceUnit(localCoords, unit);
	}

	bool UpdateTileImage(glm::ivec2 position) {
		//get chunk coords
		glm::ivec2 chunkPos = glm::ivec2(floor(position.x / (float)CHUNK_SIZE), floor(position.y / (float)CHUNK_SIZE));

		//get chunk at coords
		Chunk* chunk = GetChunk(chunkPos);

		if (chunk == nullptr) {
			return false;
		}

		//get local coords
		glm::ivec2 localCoords = position - (chunkPos * CHUNK_SIZE);

		return chunk->UpdateTileImage(localCoords);


	}

	glm::ivec2 ChunkHandler::GetWorldSize() {
		return worldSize;
	}

	Unit* ChunkHandler::GetUnit(glm::ivec2 pos) {
		glm::ivec2 chunkPos = glm::ivec2(floor(pos.x / (float)CHUNK_SIZE), floor(pos.y / (float)CHUNK_SIZE));
		glm::ivec2 unitPos = pos - (chunkPos * CHUNK_SIZE);


		Chunk* chunk = GetChunk(chunkPos);
		if (chunk == nullptr) {
			return nullptr;
		}

		return chunk->GetUnit(unitPos);

	}

	Tile* ChunkHandler::GetTile(glm::ivec2 pos) {
		glm::ivec2 chunkPos = glm::ivec2(floor(pos.x / (float)CHUNK_SIZE), floor(pos.y / (float)CHUNK_SIZE));
		glm::ivec2 unitPos = pos - (chunkPos * CHUNK_SIZE);


		Chunk* chunk = GetChunk(chunkPos);

		if (chunk == nullptr) {
			return nullptr;
		}

		return chunk->GetTile(unitPos);

	}
}
