#include "MainScene.h"
#include <iostream>

#include "Game.h"


MainScene::MainScene() : Scene("Game")
{
}


MainScene::~MainScene()
{
}

void MainScene::Init() {
	Game::Init();
}

void MainScene::Draw() {
	Game::Draw();
}

void MainScene::Update() {
	Game::Update();
}

void MainScene::Uninit() {
	Game::Uninit();
}
