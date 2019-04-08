#include "Game.h"
#include "TestRenderer.h"
#include "ChunkHandler.h"


namespace Game {
	namespace {
		TestRenderer* test;
	}

	void Game::Init() {
		ChunkHandler::Init();
		test = new TestRenderer();
	}

	void Game::Update() {
		test->Update();
	}
	void Game::Draw() {
		test->Draw();
		ChunkHandler::Draw();
	}

	void Game::Uninit() {
		ChunkHandler::Uninit();
		delete test;
	}
}
