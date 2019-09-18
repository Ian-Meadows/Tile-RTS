#pragma once
#include "Updater.h"

namespace UpdaterHandler {
	void Init();
	void Update();
	void Uninit();

	void AddUnitToUpdater(Unit* unit);
}

