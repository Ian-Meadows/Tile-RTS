#pragma once
#include "Scene.h"
#include"TestRenderer.h"

class TestUIScene :
	public Scene
{
public:
	TestUIScene();
	~TestUIScene();

	void Init();
	void Draw();
	void Update();
	void Uninit();

	TestRenderer* test;

};

