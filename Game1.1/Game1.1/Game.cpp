#include "Game.h"
#include "TestRenderer.h"


namespace Game {
	namespace {
		TestRenderer* test;
	}

	void Game::Init() {
		test = new TestRenderer();
	}

	void Game::Update() {
		test->Update();
	}
	void Game::Draw() {
		test->Draw();
	}

	void Game::Uninit() {
		delete test;
	}
}
