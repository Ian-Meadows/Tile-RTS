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
