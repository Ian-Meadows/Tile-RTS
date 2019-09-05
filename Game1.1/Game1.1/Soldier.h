#pragma once
#include "Unit.h"

#include <glm/glm.hpp>


class Soldier :
	public Unit
{
public:
	Soldier(glm::ivec2 pos);
	~Soldier();

	bool Update();

private:
	float time = 0.0f;

	glm::ivec2 pos;
};

