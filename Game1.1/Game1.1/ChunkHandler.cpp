#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>

namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		//std::unordered_map<glm::vec2, Chunk*> chunks;
	}

	void ChunkHandler::Init() {

	}

	void ChunkHandler::Draw() {

	}

	void ChunkHandler::Uninit() {
		//chunks.clear();
		for (unsigned int i = 0; i < chunksList.size(); i++) {
			delete chunksList[i];
		}
		chunksList.clear();
	}

	Chunk* ChunkHandler::GetChunk(glm::vec2) {
		return nullptr;
	}
}
