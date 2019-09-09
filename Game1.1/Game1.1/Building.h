#pragma once
#include "Unit.h"
class Building :
	public Unit
{
public:
	Building(glm::ivec2 position);
	~Building();
};

