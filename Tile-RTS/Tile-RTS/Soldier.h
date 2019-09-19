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

	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();

};

