#pragma once
#include <glm/glm.hpp>
#include "Chunk.h"

namespace ChunkHandler {
	void Init();

	void Draw();

	void Uninit();

	Chunk* GetChunk(glm::vec2);

}

