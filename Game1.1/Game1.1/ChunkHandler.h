#pragma once
#include <glm/glm.hpp>
#include "TextureAtlasCreator.h"


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
	void Init();


	void Uninit();

	Chunk* GetChunk(glm::ivec2 pos);

	//uses global coordinates
	void MoveUnit(glm::ivec2 startPosition, glm::ivec2 endPosition);

	//uses global coordinates. returns if unit could be placed
	bool PlaceUnit(glm::ivec2 postion, Unit* unit);

	TextureAtlas* GetTextureAtlas();
}

