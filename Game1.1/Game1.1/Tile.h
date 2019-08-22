#pragma once
#include <glm/glm.hpp>
#include "Unit.h"
#include "TextureAtlas.h"

enum TileType {
	Empty, Water, Fire, Biomass
};


class Tile
{
public:
	Tile(glm::ivec2 position, TileType tileType);
	~Tile();

	Unit* unit = nullptr;

	//returns texture number, and color for the unit or tile;
	glm::ivec2 GetUnitNumbers(TextureAtlas* ta);

	TileType tileType;

private:
	glm::ivec2 position;



};

