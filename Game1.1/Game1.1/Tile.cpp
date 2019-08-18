#include "Tile.h"



Tile::Tile()
{
}


Tile::~Tile()
{
}

glm::ivec2 Tile::GetUnitNumbers() {
	if (unit != nullptr) {
		if (unit->selected) {
			//negative texture to show its selected
			return glm::ivec2(-unit->texture, unit->color);
		}
		else {
			return glm::ivec2(unit->texture, unit->color);
		}
	}
	else {
		return glm::ivec2(0, 0xff0000);
	}
}
