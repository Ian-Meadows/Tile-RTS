#pragma once
#include "Unit.h"




class Soldier :
	public Unit
{
public:
	Soldier(glm::ivec2 position);
	~Soldier();

	bool Update();

private:
	float time = 0.0f;
};

