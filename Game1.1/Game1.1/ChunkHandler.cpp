#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

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
			return c;
		}
	}

	void ChunkHandler::Init() {

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
		
	}

	void ChunkHandler::Draw() {
		

		Chunk* chunk = chunks[glm::ivec2(0, 0)];
		Chunk* chunk2 = chunks[glm::ivec2(0, 1)];
		if (chunk != nullptr) {
			//chunk->Draw();
		}
		if (chunk2 != nullptr) {
			//chunk2->Draw();
		}

	}

	void ChunkHandler::Uninit() {
		chunks.clear();
		for (unsigned int i = 0; i < chunksList.size(); i++) {
			delete chunksList[i];
		}
		chunksList.clear();
	}

	//TODO::add chunk generation
	Chunk* ChunkHandler::GetChunk(glm::ivec2 pos) {
		Chunk* c = chunks[pos];
		if (c == nullptr) {
			c = CreateNewChunk(pos);
			chunks[pos] = c;
		}
		else {
			return c;
		}
		
	}
}
