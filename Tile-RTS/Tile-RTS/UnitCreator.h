#pragma once
#include "UpdaterHandler.h"
#include "ChunkHandler.h"

namespace UnitCreator {
	void Init();

	/*
	3 ways
	1: place created unit
	2: duplicate and place unit
	3: multi place
	*/

	//for single units. returns true if unit could be placed
	bool CreateUnit(Unit* unit);
	//for multi tile units
	void CreateUnit(Unit* unit, glm::ivec2* positions, unsigned int size);

	void Uninit();
}

