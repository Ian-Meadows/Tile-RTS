#include <vector>

#include "CommanderHandler.h"
#include "PlayerCommander.h"


namespace CommanderHandler {
	namespace {
		std::vector<Commander*> commanders;
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
		commanders.push_back(commander);
	}

	void DeleteCommander(Commander* commander) {

	}
}