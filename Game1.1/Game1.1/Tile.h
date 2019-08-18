#pragma once
#include <glm/glm.hpp>
#include "Unit.h"

class Tile
{
public:
	Tile();
	~Tile();

	Unit* unit = nullptr;

	//returns texture number, and color for the unit or tile;
	glm::ivec2 GetUnitNumbers();
};

