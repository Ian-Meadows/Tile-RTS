#pragma once
#include <glm/glm.hpp>
#include "TextureAtlasCreator.h"

#define INFINITE_WORLD glm::ivec2(0, 0)


class Chunk;
class Unit;

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

	//set size of world. Note:for infinite set worldSize to 0
	void Init(glm::ivec2 worldSize, bool fullyLoadWorld);


	void Uninit();

	//note: can return null with finite world size
	Chunk* GetChunk(glm::ivec2 pos);

	//uses global coordinates. 
	bool MoveUnit(glm::ivec2 startPosition, glm::ivec2 endPosition);

	//uses global coordinates. returns true if unit could be placed
	bool PlaceUnit(glm::ivec2 postion, Unit* unit);

	TextureAtlas* GetTextureAtlas();

	glm::ivec2 GetWorldSize();
}

