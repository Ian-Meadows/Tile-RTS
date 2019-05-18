#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Camera.h"
#include "Window.h"
#include "TextureAtlasCreator.h"

namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;

		Shader* shader;
		unsigned int texture;

		void InitTexture() {
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			TextureAtlas* ta = TextureAtlasCreator::GetAtlas(false);

			int size;
			char* image = ta->Compress(&size);

			if (image == nullptr) {
				std::cout << "unable to load image to texture" << std::endl;
				return;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ta->GetWidth(), ta->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			//free image
			delete[] image;

			//Shader* shader = ChunkHandler::GetShader();
			shader->use();
			shader->setInt("chunkTexture", 0);
			shader->setInt("totalImages", ta->GetTotalImages());
			shader->setInt("imgSize", ta->GetWidth());
			shader->setInt("spacing", ta->GetSpacing());
		}

	}

	void ChunkHandler::Init() {

		shader = new Shader("ChunkVertexShader.vert", "ChunkFragmentShader.frag");

		InitTexture();



		Chunk* temp = new Chunk(glm::ivec2(0, 0));
		chunks[glm::ivec2(0, 0)] = temp;
		temp = new Chunk(glm::ivec2(0, 1));
		chunks[glm::ivec2(0, 1)] = temp;
		std::unordered_map<glm::ivec2, Chunk*>::iterator it = chunks.find(glm::ivec2(0, 0));
		if (it != chunks.end()) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}

		if (chunks[glm::ivec2(0, 1)] != nullptr) {
			std::cout << "found" << std::endl;
		}
		else {
			std::cout << "not found" << std::endl;
		}
		shader->use();
		shader->setInt("chunkSize", CHUNK_SIZE);
	}

	void ChunkHandler::Draw() {
		shader->use();
		shader->setMat4("view", Camera::GetView());
		shader->setMat4("projection", Window::GetPerspective());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		Chunk* chunk = chunks[glm::ivec2(0, 0)];
		Chunk* chunk2 = chunks[glm::ivec2(0, 1)];
		if (chunk != nullptr) {
			chunk->Draw();
		}
		if (chunk2 != nullptr) {
			chunk2->Draw();
		}

	}

	void ChunkHandler::Uninit() {
		chunks.clear();
		for (unsigned int i = 0; i < chunksList.size(); i++) {
			delete chunksList[i];
		}
		chunksList.clear();

		//TODO: delete texure

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
