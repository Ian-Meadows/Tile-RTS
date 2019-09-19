#include "PlayerCommander.h"

#include <iostream>
#include <math.h>

#include "Input.h"
#include "Camera.h"
#include "ChunkHandler.h"
#include "UpdaterHandler.h"


#include "Debugger.h"


PlayerCommander::PlayerCommander(int color) : Commander()
{
	this->color = color;
}


PlayerCommander::~PlayerCommander()
{
}

void PlayerCommander::Update() {
	if (Input::GetMouseButtonPressed(0) && !Input::GetMouseOverUI()) {
		LeftClick();
	}
	if (Input::GetMouseButtonPressed(1) && !Input::GetMouseOverUI()) {
		RightClick();
	}
}

void PlayerCommander::RightClick() {
	glm::vec2 posf = Camera::ScreenToWorld(Input::GetMousePosition());

	glm::ivec2 pos = glm::ivec2(floor(posf.x), floor(posf.y));

	Unit* unitTarget = ChunkHandler::GetUnit(pos);
	if (unitTarget != nullptr) {
		SetSelectedUnitsTarget(unitTarget);
	}
	else {
		Tile* tileTarget = ChunkHandler::GetTile(pos);
		SetSelectedUnitsTarget(tileTarget);
	}

}

void PlayerCommander::LeftClick() {
	ClearUnitsSelected();

	glm::vec2 posf = Camera::ScreenToWorld(Input::GetMousePosition());

	glm::ivec2 pos = glm::ivec2(floor(posf.x), floor(posf.y));

	

	Unit* unit = ChunkHandler::GetUnit(pos);
	if (unit != nullptr && unit->commanderID == ID) {

		unit->Select();
		unitsSelected.push_back(unit);
	}
	else {
		Debugger::PrintVector(posf, "mouse float pos");
		Debugger::PrintVector(pos, "mouse pos");
	}
}

void PlayerCommander::ClearUnitsSelected() {
	for (unsigned int i = 0; i < unitsSelected.size(); ++i) {
		if (unitsSelected[i]->GetSelected()) {
			unitsSelected[i]->Select();
		}
	}
	unitsSelected.clear();
}

void PlayerCommander::SetSelectedUnitsTarget(Tile* target) {
	for (int i = 0; i < unitsSelected.size(); ++i) {
		if (unitsSelected[i] != nullptr) {
			unitsSelected[i]->SetTarget(target);
			if (!unitsSelected[i]->GetIsUpdating()) {
				UpdaterHandler::AddUnitToUpdater(unitsSelected[i]);
			}
			
		}
	}
}
void PlayerCommander::SetSelectedUnitsTarget(Unit* target) {
	for (int i = 0; i < unitsSelected.size(); ++i) {
		if (unitsSelected[i] != nullptr) {
			unitsSelected[i]->SetTarget(target);
			if (!unitsSelected[i]->GetIsUpdating()) {
				UpdaterHandler::AddUnitToUpdater(unitsSelected[i]);
			}
		}
	}
}
