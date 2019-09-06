#include "Unit.h"



Unit::Unit()
{
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
