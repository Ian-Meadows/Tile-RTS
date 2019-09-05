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
	return true;
}

double Unit::GetUpdateRate() {
	return ur;
}
