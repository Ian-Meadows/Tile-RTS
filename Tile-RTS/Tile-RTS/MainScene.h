#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	void Init();
	void Draw();
	void Update();
	void Uninit();
};

