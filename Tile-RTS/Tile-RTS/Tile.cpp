#include "Tile.h"
#include "TileBackgroundHandler.h"



Tile::Tile(glm::ivec2 position, TileType tileType)
{
	this->position = position;
	this->tileType = tileType;
}


Tile::~Tile()
{
	if (unit != nullptr) {
		delete unit;
	}
}

int Tile::GetColorWithBGTile(int color, int tile) {
	return color | (tile << 24);
}

glm::ivec2 Tile::GetUnitNumbers(TextureAtlas* ta) {
	if (unit != nullptr) {
		if (unit->selected) {
			//negative texture to show its selected
			//return glm::ivec2(-unit->texture, unit->color);
			return glm::ivec2(-unit->texture, GetColorWithBGTile(unit->color,
				TileBackgroundHandler::GetBackgroundLocation(GetTileTypeString(tileType))));
		}
		else {
			//return glm::ivec2(unit->texture, unit->color);
			return glm::ivec2(unit->texture, GetColorWithBGTile(unit->color,
				TileBackgroundHandler::GetBackgroundLocation(GetTileTypeString(tileType))));
		}
	}
	else {
		return TileBackgroundHandler::GetBackgroundInfo(GetTileTypeString(tileType));
	}
}

std::string Tile::GetTileTypeString(TileType tt) {
	switch (tt) {
		case Empty:
			return "Black blank";
			break;
		case Fire:
			return "Red blank";
			break;
		case Water:
			return "Blue blank";
			break;
		case Biomass:
			return "Green blank";
			break;
		default:
			return "Black blank";
			break;
	}
}
