#include <math.h>
#include "Game.h"
#include "TestRenderer.h"
#include "ChunkHandler.h"
#include "ChunkRenderHandler.h"
#include "ChunkGenerator.h"
#include "ImageTester.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"
#include "Soldier.h"


namespace Game {
	namespace {
		TestRenderer* test;
		ImageTester* it;

		double time = 0.0;

		Soldier* temp;

	}

	void Game::Init() {
		ChunkHandler::Init();
		ChunkRenderHandler::Init();
		ChunkGenerator::Init();
		test = new TestRenderer();
		it = new ImageTester();

		temp = new Soldier(glm::ivec2(5, 5));
		//place unit
		ChunkHandler::PlaceUnit(glm::ivec2(5, 5), temp);


	}

	void Game::Update() {
		test->Update();
		it->Update();

		temp->Update();

		/*
		time += Time::GetDeltaTime();
		if (time > 1.0) {
			time = 0;
			glm::vec2 mousePos = Input::GetMousePosition();
			std::cout << "Mouse Pos: X: " << mousePos.x << " Y: " << mousePos.y << std::endl;

			glm::vec3 cameraPos = Camera::ScreenToWorld(mousePos);
			std::cout << "Camera Pos: X: " << cameraPos.x << " Y: " << cameraPos.y << " Z: " << cameraPos.z << std::endl;

			glm::vec3 worldPos = Camera::ScreenToWorld(mousePos);
			std::cout << "World Pos: X: " << floor(worldPos.x / 32.0f) << " Y: " << floor(worldPos.y / 32.0f) << std::endl;
		}
		*/
		

	}
	void Game::Draw() {
		test->Draw();
		ChunkRenderHandler::Draw();
		it->Draw();
	}

	void Game::Uninit() {
		ChunkGenerator::Uninit();
		ChunkHandler::Uninit();
		ChunkRenderHandler::UnInit();
		delete test;
		delete it;
	}
}
