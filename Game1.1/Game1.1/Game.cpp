#include "Game.h"
#include "TestRenderer.h"
#include "ChunkHandler.h"
#include "ImageTester.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"

namespace Game {
	namespace {
		TestRenderer* test;
		ImageTester* it;

		double time = 0.0;

	}

	void Game::Init() {
		ChunkHandler::Init();
		test = new TestRenderer();
		it = new ImageTester();
	}

	void Game::Update() {
		test->Update();
		it->Update();

		time += Time::GetDeltaTime();
		if (time > 1.0) {
			time = 0;
			glm::vec2 mousePos = Input::GetMousePosition();
			std::cout << "Mouse Pos: X: " << mousePos.x << " Y: " << mousePos.y << std::endl;

			glm::vec3 cameraPos = Camera::GetPosition();
			std::cout << "Camera Pos: X: " << cameraPos.x << " Y: " << cameraPos.y << "Z: " << cameraPos.z << std::endl;

			glm::vec3 worldPos = Camera::ScreenToWorld(mousePos);
			std::cout << "World Pos: X: " << worldPos.x << " Y: " << worldPos.y << std::endl;

			
		}

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
