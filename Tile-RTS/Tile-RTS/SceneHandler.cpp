#include "SceneHandler.h"
#include <vector>
#include <iostream>


namespace SceneHandler {
	namespace {
		std::vector<Scene*> scenes;
		int currentScene;
	}

	void Init() {
		currentScene = -1;
	}
	void Update() {
		if (currentScene >= 0 && scenes[currentScene] != nullptr) {
			scenes[currentScene]->DeleteOldUIElements();
			scenes[currentScene]->Update();
		}
	}
	void Draw() {
		if (currentScene >= 0 && scenes[currentScene] != nullptr) {
			scenes[currentScene]->Draw();
		}
	}
	void Uninit() {
		if (currentScene >= 0 && scenes[currentScene] != nullptr) {
			scenes[currentScene]->_Uninit();
		}
		for (unsigned int i = 0; i < scenes.size(); i++) {
			delete scenes[i];
		}
	}

	Scene* GetCurrentScene() {
		return scenes[currentScene];
	}

	void AddScene(Scene* scene) {
		scenes.push_back(scene);
	}

	void SetCurrentScene(std::string name) {
		for (unsigned int i = 0; i < scenes.size(); i++) {
			if (scenes[i]->name == name) {
				
				if (currentScene >= 0 && scenes[currentScene] != nullptr) {
					scenes[currentScene]->isActive = false;
					scenes[currentScene]->_Uninit();
				}
				currentScene = i;
				scenes[currentScene]->isActive = true;
				scenes[currentScene]->_Init();
				return;
			}
		}
		std::cout << "ERROR::Scene " << name << " does not exist" << std::endl;
	}
}