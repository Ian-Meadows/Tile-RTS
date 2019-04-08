#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Camera.h"
#include "Window.h"

namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;

		Shader* shader;
	}

	void ChunkHandler::Init() {

		shader = new Shader("ChunkVertexShader.vert", "ChunkFragmentShader.frag");

		Chunk* temp = new Chunk(glm::ivec2(0, 0));
		chunks[glm::ivec2(0, 0)] = temp;
		std::unordered_map<glm::ivec2, Chunk*>::iterator it = chunks.find(glm::ivec2(0, 0));
		if (it != chunks.end()) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}

		if (chunks[glm::ivec2(0, 0)] != nullptr) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}

	}

	void ChunkHandler::Draw() {
		shader->use();
		shader->setMat4("view", Camera::GetView());
		shader->setMat4("perspective", Window::GetPerspective());

		Chunk* chunk = chunks[glm::ivec2(0, 0)];
		if (chunk != nullptr) {
			chunk->Draw();
		}
	}

	void ChunkHandler::Uninit() {
		chunks.clear();
		for (unsigned int i = 0; i < chunksList.size(); i++) {
			delete chunksList[i];
		}
		chunksList.clear();
		delete shader;
	}

	/*
	Chunk* ChunkHandler::GetChunk(glm::ivec2 pos) {
		return nullptr;
	}
	*/

	Shader* GetShader() {
		return ChunkHandler::shader;
	}
}
