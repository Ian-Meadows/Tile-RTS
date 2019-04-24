#include "Game.h"
#include "TestRenderer.h"
#include "ChunkHandler.h"
#include "ImageTester.h"


namespace Game {
	namespace {
		TestRenderer* test;
		ImageTester* it;
	}

	void Game::Init() {
		ChunkHandler::Init();
		test = new TestRenderer();
		it = new ImageTester();
	}

	void Game::Update() {
		test->Update();
		it->Update();
	}
	void Game::Draw() {
		test->Draw();
		ChunkHandler::Draw();
		it->Draw();
	}

	void Game::Uninit() {
		ChunkHandler::Uninit();
		delete test;
		delete it;
	}
}
