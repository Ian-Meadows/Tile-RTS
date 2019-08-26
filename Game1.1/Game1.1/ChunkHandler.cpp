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


#include "stb_image.h"

namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;


		Chunk* CreateNewChunk(glm::ivec2 pos) {
			Chunk* c = new Chunk(pos);
			chunksList.push_back(c);
			chunks[pos] = c;
			return c;
		}

		TextureAtlas* ta;

	}

	void ChunkHandler::Init() {
		/*
		Chunk* temp = new Chunk(glm::ivec2(0, 0));
		chunks[glm::ivec2(0, 0)] = temp;
		temp = new Chunk(glm::ivec2(0, 1));
		chunks[glm::ivec2(0, 1)] = temp;
		std::unordered_map<glm::ivec2, Chunk*>::iterator it = chunks.find(glm::ivec2(0, 0));
		if (it != chunks.end()) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}

		if (chunks[glm::ivec2(0, 1)] != nullptr) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}
		*/

		ta = TextureAtlasCreator::GetAtlas(false);
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


	void ChunkHandler::MoveUnit(glm::ivec2 startPosition, glm::ivec2 endPosition) {
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

		glm::ivec2 localStartPos = startPosition - (startChunkPos * CHUNK_SIZE);
		glm::ivec2 localEndPos = endPosition - (endChunkPos * CHUNK_SIZE);

		if (endChunk->GetUnit(localEndPos) != nullptr) {
			//unable to move unit location is occupied
			std::cout << "Unable to move unit location is occupied" << std::endl;
			return;
		}

		Unit* unitToMove = startChunk->GetUnit(localStartPos);
		if (unitToMove == nullptr || !unitToMove->IsMovable()) {
			//unit does not exist or is immobile
			std::cout << "Unable to move unit" << std::endl;
			return;
		}

		//move
		endChunk->PlaceUnit(localEndPos, unitToMove);
		//clear old location
		startChunk->ClearUnit(localStartPos);

	}
}
