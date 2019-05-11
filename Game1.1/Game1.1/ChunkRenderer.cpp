#include "ChunkRenderer.h"
#include "Chunk.h"
#include "ChunkHandler.h"
#include "Window.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextureAtlasCreator.h"



ChunkRenderer::ChunkRenderer(Chunk* chunk)
{
	this->chunk = chunk;

	

	Init();
	SetPositions();
	SetUnitInfo(true);
	SetTextureCoordinates();
	InitTexture();
}


ChunkRenderer::~ChunkRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(CHUNK_SIZE * CHUNK_SIZE, VBO);
	glDeleteBuffers(1, &EBO);

	delete positions;
	delete unitNumbers;
}


void ChunkRenderer::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(4, VBO);
	glGenBuffers(1, &EBO);

	float vert[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indi[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}



void ChunkRenderer::SetPositions() {
	positions = new glm::ivec2[CHUNK_SIZE * CHUNK_SIZE];

	int i = 0;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			positions[i] = glm::ivec2(x, y);
			i++;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), &positions[0], GL_STATIC_DRAW);

	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::ivec2), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
}

void ChunkRenderer::SetUnitInfo(bool firstTime) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	if (firstTime) {
		unitNumbers = new glm::ivec2[CHUNK_SIZE * CHUNK_SIZE];

		int i = 0;
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				if (x > 2 && x < CHUNK_SIZE - 2 && y > 2 && y < CHUNK_SIZE - 2) {
					unitNumbers[i] = glm::ivec2(0, 0x9C1BF3);
				}
				else {
					unitNumbers[i] = glm::ivec2(1, 0xffffff);
				}
				
				i++;
			}
		}

		glBufferData(GL_ARRAY_BUFFER, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), &unitNumbers[0], GL_DYNAMIC_DRAW);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::ivec2), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);
	}
	else {

	}
}

void ChunkRenderer::SetTextureCoordinates() {

	TextureAtlas* ta = TextureAtlasCreator::GetAtlas(false);

	float diff = ta->GetSpacing() * ta->GetTotalImagesInLength() / (float)ta->GetWidth();

	
	float texCoords[] = {
		1.0f - diff, 1.0f - diff,
		1.0f - diff, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f - diff
	};
	

	/*
	float texCoords[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	*/

	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
}

void ChunkRenderer::InitTexture() {
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

	Shader* shader = ChunkHandler::GetShader();
	shader->use();
	shader->setInt("chunkTexture", 0);
	shader->setInt("totalImages", ta->GetTotalImages());
	shader->setInt("imgSize", ta->GetWidth());
	shader->setInt("spacing", ta->GetSpacing());
}

void ChunkRenderer::Draw() {

	//SetUnitNumbers(false);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, CHUNK_SIZE * CHUNK_SIZE);


}

