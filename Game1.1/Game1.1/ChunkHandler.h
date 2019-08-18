#pragma once
#include <glm/glm.hpp>

class Chunk;

struct GLMKeyFunctions {
	size_t operator()(const glm::ivec2& k)const
	{
		//zor x and y
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

namespace ChunkHandler {
	void Init();


	void Uninit();

	Chunk* GetChunk(glm::ivec2 pos);

}

