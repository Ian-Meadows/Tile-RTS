#include "ChunkHandler.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Window.h"
#include "TextureAtlasCreator.h"
#include "Chunk.h"


#include "stb_image.h"

namespace ChunkHandler {
	namespace {
		std::vector<Chunk*> chunksList;
		std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;

		Shader* shader;
		unsigned int texture, unitSelectionTexture;

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

		void LoadUnitSelectionTexture(const char* textureFilePath) {
			glGenTextures(1, &unitSelectionTexture);
			glBindTexture(GL_TEXTURE_2D, unitSelectionTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			int width;
			int height;
			int nrChannels;
			unsigned char *image = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);
			if (image == NULL) {
				std::cout << "ERROR::Unable to load unit selection texture" << std::endl;
				return;
			}
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			stbi_image_free(image);

			shader->use();
			shader->setInt("unitSelectionTexture", 1);
			shader->setVec3("unitSelectionColor", glm::vec3(0.0f, 1.0f, 0.0f));
		}

	}

	void ChunkHandler::Init() {

		shader = new Shader("ChunkVertexShader.vert", "ChunkFragmentShader.frag");

		InitTexture();
		LoadUnitSelectionTexture("Images/OutLine.png");


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
		//send over constants to gpu
		shader->setInt("SOLIDCOLOR", SOLIDCOLOR);
	}

	void ChunkHandler::Draw() {
		shader->use();
		shader->setMat4("view", Camera::GetView());
		shader->setMat4("projection", Window::GetPerspective());

		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindTexture(GL_TEXTURE_2D, unitSelectionTexture);

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

		glDeleteTextures(1, &texture);
		glDeleteTextures(1, &unitSelectionTexture);

		delete shader;
	}

	
	Chunk* ChunkHandler::GetChunk(glm::ivec2 pos) {
		return chunks[pos];
	}
	

	Shader* GetShader() {
		return ChunkHandler::shader;
	}
}
