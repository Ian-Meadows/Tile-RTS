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
	//note: y is color, but has background tile transplanted in it.
	glm::ivec2 GetUnitNumbers(TextureAtlas* ta);

	TileType tileType;

private:
	glm::ivec2 position;

	std::string GetTileTypeString(TileType tt);

	int GetColorWithBGTile(int color, int tile);

};

