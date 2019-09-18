#pragma once
#include "Commander.h"
class PlayerCommander :
	public Commander
{
public:
	PlayerCommander(int color);
	~PlayerCommander();

	void Update();
};

