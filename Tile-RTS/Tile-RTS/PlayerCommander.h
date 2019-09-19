#pragma once
#include "Commander.h"
#include <vector>
#include "Unit.h"

class PlayerCommander :
	public Commander
{
public:
	PlayerCommander(int color);
	~PlayerCommander();

	void Update();

private:
	std::vector<Unit*> unitsSelected;

	void ClearUnitsSelected();

	void SetSelectedUnitsTarget(Tile* target);
	void SetSelectedUnitsTarget(Unit* target);

	void RightClick();
	void LeftClick();

};

