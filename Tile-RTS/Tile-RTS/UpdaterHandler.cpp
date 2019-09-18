#include "UpdaterHandler.h"

#include <vector>


namespace UpdaterHandler {
	namespace {
		std::vector<Updater*> updaters;
	}

	void Init() {

	}
	void Update() {
		for (unsigned int i = 0; i < updaters.size(); ++i) {
			updaters[i]->Update();
		}
	}
	void Uninit() {
		for (unsigned int i = 0; i < updaters.size(); ++i) {
			delete updaters[i];
		}
	}

	void AddUnitToUpdater(Unit* unit) {
		for (unsigned int i = 0; i < updaters.size(); ++i) {
			if ((updaters[i])->GetUpdateTime() == unit->GetUpdateRate()) {
				updaters[i]->AddUnit(unit);
				return;
			}
		}

		Updater* newUpdater = new Updater(unit->GetUpdateRate());
		newUpdater->AddUnit(unit);
		updaters.push_back(newUpdater);
	}
}
