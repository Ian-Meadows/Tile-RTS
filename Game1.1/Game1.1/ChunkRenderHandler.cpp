#include "ChunkRenderHandler.h"
#include <vector>
#include <math.h>

#include "Camera.h"
#include "Window.h"
#include "TextureAtlasCreator.h"
#include "Chunk.h"
#include "ChunkHandler.h"

#include "Debugger.h"

#include "stb_image.h"

#define INITIALRENDERERS 9

namespace ChunkRenderHandler {
	namespace {
		std::vector<ChunkRenderer*> renderersInUse;
		std::vector<ChunkRenderer*> renderersNotInUse;
		int totalRenderers = 0;

		Shader* shader;
		unsigned int texture, unitSelectionTexture;

		void CreateNewChunkRenderer() {
			renderersNotInUse.push_back(new ChunkRenderer());
			totalRenderers++;
		}

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

		void AssignChunksToRender() {
			//TODO:actually draw the chunks
			//first create render square(location where chunks get rendered)

			int width = Window::GetWidth();
			int height = Window::GetHeight();

			//get render square 2 corners from screen to world coords
			glm::vec2 upperLeftf = Camera::ScreenToWorld(glm::vec2(0, 0));
			glm::vec2 bottomRightf = Camera::ScreenToWorld(glm::vec2(width, height));



			//convert from world coords to chunk coords
			glm::ivec2 upperLeft = glm::ivec2(floor(upperLeftf.x / ((float)CHUNK_SIZE)), floor(upperLeftf.y / (float)CHUNK_SIZE));
			glm::ivec2 bottomRight = glm::ivec2(floor(bottomRightf.x / ((float)CHUNK_SIZE)), floor(bottomRightf.y / (float)CHUNK_SIZE));

			//setup corners
			int startX = upperLeft.x;
			int startY = upperLeft.y;
			int endX = bottomRight.x;
			int endY = bottomRight.y;


			int arrayWidth = endX - startX;
			int arrayHeight = endY - startY;
			//create mask to remove the negative bit
			int mask = (1 << 31) - 1;
			//remove negative bit
			arrayWidth &= mask;
			arrayHeight &= mask;

			//init bool 2d array for chunks to render
			bool** chunksRendered = new bool*[arrayWidth];
			for (int x = 0; x < arrayWidth; x++) {
				chunksRendered[x] = new bool[arrayHeight];
				for (int y = 0; y < arrayHeight; y++) {
					chunksRendered[x][y] = false;
				}
			}
			//set chunks already being rendered
			for (int i = 0; i < renderersInUse.size(); i++) {
				glm::ivec2 pos = renderersInUse[i]->GetChunk()->GetPosition();
				if (pos.x >= startX && pos.y >= startY && pos.x <= endX && pos.y <= endY) {
					chunksRendered[pos.x][pos.y] = true;
				}
				else {
					//TODO::remove from rendering

				}
			}

			//setup renderers not in use
			for (int x = 0; x < arrayWidth; x++) {
				for (int y = 0; y < arrayHeight; y++) {
					if (!chunksRendered[x][y]) {
						//TODO::set renderers not in use to chunks to be rendered
					}
				}
			}

			
		}

		//temp
		ChunkRenderer* cr1;
		ChunkRenderer* cr2;
	}

	void ChunkRenderHandler::Init() {

		shader = new Shader("ChunkVertexShader.vert", "ChunkFragmentShader.frag");

		InitTexture();
		LoadUnitSelectionTexture("Images/OutLine.png");

		//create initial renderers
		for (int i = 0; i < INITIALRENDERERS; i++) {
			CreateNewChunkRenderer();
		}

		cr1 = new ChunkRenderer();
		cr2 = new ChunkRenderer();

		cr1->SetChunk(ChunkHandler::GetChunk(glm::ivec2(0, 0)));
		cr2->SetChunk(ChunkHandler::GetChunk(glm::ivec2(0, 1)));

		shader->use();
		shader->setInt("chunkSize", CHUNK_SIZE);
		//send over constants to gpu
		shader->setInt("SOLIDCOLOR", SOLIDCOLOR);
	}
	void ChunkRenderHandler::Draw() {
		shader->use();
		shader->setMat4("view", Camera::GetView());
		shader->setMat4("projection", Window::GetPerspective());

		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindTexture(GL_TEXTURE_2D, unitSelectionTexture);

		//TODO::finish
		AssignChunksToRender();

		//TODO::have renderers draw
		for (int i = 0; i < renderersInUse.size(); i++) {

		}

		cr1->Draw();
		cr2->Draw();

	}

	void ChunkRenderHandler::UnInit() {
		//delete all chunk renderers
		for (int i = 0; i < renderersInUse.size(); i++) {
			if (renderersInUse[i] != nullptr) {
				delete renderersInUse[i];
			}
		}
		for (int i = 0; i < renderersNotInUse.size(); i++) {
			if (renderersNotInUse[i] != nullptr) {
				delete renderersNotInUse[i];
			}
		}

		delete cr1;
		delete cr2;

		//delete textures
		glDeleteTextures(1, &texture);
		glDeleteTextures(1, &unitSelectionTexture);

		delete shader;

	}

	Shader* ChunkRenderHandler::GetShader() {
		return shader;
	}
}
