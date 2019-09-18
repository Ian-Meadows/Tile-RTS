#include "UnitCreator.h"



namespace UnitCreator {
	namespace {

	}


	void Init() {

	}

	void Uninit() {

	}

	
	bool CreateUnit(Unit* unit) {
		
		if (ChunkHandler::PlaceUnit(unit->GetPosition(), unit)) {
			UpdaterHandler::AddUnitToUpdater(unit);
			return true;
		}
		else {
			return false;
		}
	}

	//todo:make sure this works
	//todo:undo changes if failed
	void CreateUnit(Unit* unit, glm::ivec2* positions, unsigned int size) {
		UpdaterHandler::AddUnitToUpdater(unit);
		for (unsigned int i = 0; i < size; ++i) {
			ChunkHandler::PlaceUnit(positions[i], unit);
		}
	}
}
