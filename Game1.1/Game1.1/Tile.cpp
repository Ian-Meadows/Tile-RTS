#include "Tile.h"



Tile::Tile(glm::ivec2 position, TileType tileType)
{
	this->position = position;
	this->tileType = tileType;
}


Tile::~Tile()
{
}

glm::ivec2 Tile::GetUnitNumbers(TextureAtlas* ta) {
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
		switch (tileType) {
		case Empty:
			return glm::ivec2(ta->GetImageLocation("none"), 0x000000);
			break;
		case Fire:
			return glm::ivec2(ta->GetImageLocation("none"), 0xff0000);
			break;
		case Water:
			return glm::ivec2(ta->GetImageLocation("none"), 0x0000ff);
			break;
		case Biomass:
			return glm::ivec2(ta->GetImageLocation("none"), 0x00ff00);
			break;
		default:
			return glm::ivec2(ta->GetImageLocation("none"), 0xffffff);
			break;
		}
		
	}
}
