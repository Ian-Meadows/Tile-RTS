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
#include "UpdaterHandler.h"
#include "UnitCreator.h"


namespace Game {
	namespace {
		TestRenderer* test;
		ImageTester* it;

		double time = 0.0;

		

	}

	void Game::Init() {
		ChunkHandler::Init(INFINITE_WORLD, false);
		ChunkRenderHandler::Init();
		ChunkGenerator::Init();

		UpdaterHandler::Init();

		test = new TestRenderer();
		it = new ImageTester();

		UnitCreator::CreateUnit(new Soldier(glm::ivec2(5, 5)));
		UnitCreator::CreateUnit(new Soldier(glm::ivec2(-5, 5)));
		UnitCreator::CreateUnit(new Soldier(glm::ivec2(-5, -5)));
		UnitCreator::CreateUnit(new Soldier(glm::ivec2(5, -5)));
	}

	void Game::Update() {

		UpdaterHandler::Update();

		test->Update();
		it->Update();

		//temp->Update();

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
		//test->Draw();
		ChunkRenderHandler::Draw();
		//it->Draw();
	}

	void Game::Uninit() {
		ChunkGenerator::Uninit();
		ChunkHandler::Uninit();
		ChunkRenderHandler::UnInit();
		UpdaterHandler::Uninit();
		delete test;
		delete it;
	}
}
