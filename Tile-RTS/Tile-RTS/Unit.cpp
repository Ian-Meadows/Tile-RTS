#include "Unit.h"



Unit::Unit(glm::ivec2 position)
{
	this->position = position;
}


Unit::~Unit()
{
}

bool Unit::IsMovable() {
	return movable;
}

bool Unit::Update() {
	return false;
}

double Unit::GetUpdateRate() {
	return ur;
}

glm::ivec2 Unit::GetPosition() {
	return position;
}

void Unit::Select() {
	selected = !selected;
	if (!ChunkHandler::UpdateTileImage(position)) {
		std::cout << "Failed to update image" << std::endl;
	}
}

bool Unit::GetSelected() {
	return selected;
}

void Unit::SetTarget(Tile* tile) {
	tileTarget = tile;
	unitTarget = nullptr;
}
void Unit::SetTarget(Unit* unit) {
	unitTarget = unit;
	tileTarget = nullptr;
}
void Unit::SetTarget(Tile* tile, Unit* unit) {
	tileTarget = tile;
	unitTarget = unit;
}

bool Unit::GetIsUpdating() {
	return isUpdating;
}
