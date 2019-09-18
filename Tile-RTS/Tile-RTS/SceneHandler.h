#pragma once
#include "Scene.h"

namespace SceneHandler {
	void Init();
	void Update();
	void Draw();
	void Uninit();

	void AddScene(Scene* scene);
	Scene* GetCurrentScene();

	void SetCurrentScene(std::string name);

}

