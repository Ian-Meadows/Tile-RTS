#include "TileBackgroundHandler.h"
#include <iostream>

namespace TileBackgroundHandler {
	namespace {

		

		int currentIndex = 0;
		TileBackground* tileBackgrounds[MAX_BG_TEXTURES];


		bool BackgroundExists(std::string name) {
			for (int i = 0; i < MAX_BG_TEXTURES; i++) {
				if (tileBackgrounds[i] == nullptr) {
					return false;
				}
				else if (tileBackgrounds[i]->name == name) {
					return true;
				}
			}
			return false;
			
		}

	}

	void TileBackgroundHandler::Init() {
		for (int i = 0; i < MAX_BG_TEXTURES; i++) {
			tileBackgrounds[i] = nullptr;
		}
	}

	void TileBackgroundHandler::Uninit() {
		for (int i = 0; i < MAX_BG_TEXTURES; i++) {
			if (tileBackgrounds[i] != nullptr) {
				delete tileBackgrounds[i];
			}
		}
	}

	void TileBackgroundHandler::AddTileBackground(std::string name, glm::ivec2 info) {
		if (currentIndex >= MAX_BG_TEXTURES) {
			std::cout << "Unable to add more background tile texures" << std::endl;
			return;
		}
		if (BackgroundExists(name)) {
			std::cout << "background name is already in use" << std::endl;
			return;
		}
		tileBackgrounds[currentIndex] = new TileBackground(name, info);


		currentIndex++;
	}

	glm::ivec2 TileBackgroundHandler::GetBackgroundInfo(std::string name) {
		for (int i = 0; i < MAX_BG_TEXTURES; i++) {
			if (tileBackgrounds[i]->name == name) {
				return tileBackgrounds[i]->info;
			}
		}
		std::cout << name << " does not exist as a background texture" << std::endl;
		return glm::ivec2(-1, -1);
	}

	int GetBackgroundLocation(std::string name) {
		for (int i = 0; i < MAX_BG_TEXTURES; i++) {
			if (tileBackgrounds[i]->name == name) {
				return i;
			}
		}
		std::cout << name << " does not exist as a background texture" << std::endl;
		return -1;
	}

	glm::ivec2* TileBackgroundHandler::GetAllBackgroundInfo() {
		glm::ivec2 backgrounds[MAX_BG_TEXTURES];
		for (int i = 0; i < MAX_BG_TEXTURES; i++) {
			if (tileBackgrounds[i] != nullptr) {
				backgrounds[i] = tileBackgrounds[i]->info;
			}
			else {
				backgrounds[i] = glm::ivec2(-1, -1);
			}
			
		}
		return backgrounds;
	}

}
