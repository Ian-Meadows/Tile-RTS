#include <vector>

#include "CommanderHandler.h"
#include "PlayerCommander.h"


namespace CommanderHandler {
	namespace {
		std::vector<Commander*> commanders;

		int currentCommanderID = 0;
	}
	void Init() {
		AddCommander(new PlayerCommander(0x5050ff));
	}
	void Update() {
		for (unsigned int i = 0; i < commanders.size(); ++i) {
			if (commanders[i] != nullptr) {
				commanders[i]->Update();
			}
		}
	}
	void Uninit() {
		for (unsigned int i = 0; i < commanders.size(); ++i) {
			if (commanders[i] != nullptr) {
				delete commanders[i];
			}
			
		}
	}

	void AddCommander(Commander* commander) {
		commander->ID = currentCommanderID;
		commanders.push_back(commander);
		++currentCommanderID;
	}

	Commander* GetCommander(int index) {
		if (index >= commanders.size()) {
			return nullptr;
		}
		else {
			return commanders[index];
		}
	}
}