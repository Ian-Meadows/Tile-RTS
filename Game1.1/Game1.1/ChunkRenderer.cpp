#include "ChunkRenderer.h"
#include "Chunk.h"
#include "ChunkRenderHandler.h"
#include "Window.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextureAtlasCreator.h"


#include "Debugger.h"


ChunkRenderer::ChunkRenderer()
{

	

	Init();
	SetPositions();
	SetUnitInfo(true);
	SetTextureCoordinates();
	SetBasicTextureCoordinates();
}


ChunkRenderer::~ChunkRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(4, VBO);
	glDeleteBuffers(1, &EBO);

	delete[] positions;
	delete[] unitNumbers;
}

void ChunkRenderer::SetChunk(Chunk* chunk) {
	this->chunk = chunk;
	chunk->SetChunkRenderer(this);
}


Chunk* ChunkRenderer::GetChunk() {
	return chunk;
}


void ChunkRenderer::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(5, VBO);
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

	TextureAtlas* ta = TextureAtlasCreator::GetAtlas(false);

	if (firstTime) {
		unitNumbers = new glm::ivec2[CHUNK_SIZE * CHUNK_SIZE];

		
		/*
		int i = 0;
		for (int x = 0; x < CHUNK_SIZE; ++x) {
			for (int y = 0; y < CHUNK_SIZE; ++y) {
				unitNumbers[i] = glm::ivec2(ta->GetImageLocation("none"), 0x9C1BF3);
				
				++i;
			}
		}
		*/
		glBufferData(GL_ARRAY_BUFFER, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), NULL, GL_STREAM_DRAW);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::ivec2), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);
	}
	else {


		int i = 0;
		for (int x = 0; x < CHUNK_SIZE; ++x) {
			for (int y = 0; y < CHUNK_SIZE; ++y) {
				unitNumbers[i] = chunk->GetTileInfo(glm::ivec2(x, y), ta);

				++i;
			}
		}


		//glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
		//glBufferSubData(GL_ARRAY_BUFFER, 0, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), &unitNumbers[0]);
		//glBufferData(GL_ARRAY_BUFFER, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), NULL, GL_STREAM_DRAW);

		/*
		void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		// now copy data into memory
		memcpy(ptr, unitNumbers, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2));
		// make sure to tell OpenGL we're done with the pointer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/

		/*
		//void *glMapBufferRange(GLenum target​, GLintptr offset​, GLsizeiptr length​, GLbitfield access​);
		void* ptr = glMapBufferRange(GL_ARRAY_BUFFER, 0, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy(ptr, unitNumbers, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2));
		// make sure to tell OpenGL we're done with the pointer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/

		void* ptr = glMapBufferRange(GL_ARRAY_BUFFER, 0, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		
		if (ptr == nullptr) {
			std::cout << "buffer range is null" << std::endl;
			return;
		}
		memcpy(ptr, unitNumbers, CHUNK_SIZE * CHUNK_SIZE * sizeof(glm::ivec2));
		// make sure to tell OpenGL we're done with the pointer
		glUnmapBuffer(GL_ARRAY_BUFFER);



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

void ChunkRenderer::SetBasicTextureCoordinates() {
	float texCoords[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(4);

}



void ChunkRenderer::UpdateSingleUnitRender(glm::ivec2 position, glm::ivec2 info) {


	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);

	int maxSize = CHUNK_SIZE * CHUNK_SIZE;

	//TODO::might wanna swap x and y
	//int pos = position.x + (position.y * CHUNK_SIZE);
	int pos = position.y + (position.x * CHUNK_SIZE);


	//glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
	glBufferSubData(GL_ARRAY_BUFFER, pos * sizeof(glm::ivec2), sizeof(glm::ivec2), &info);

}


void ChunkRenderer::RenderSetup() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::ivec2 position = chunk->GetPosition();

	//do math to create model
	model = glm::translate(model, glm::vec3(position.x * CHUNK_SIZE * UNIT_SIZE, position.y * CHUNK_SIZE * UNIT_SIZE, 0));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE));

	//set model on gpu
	ChunkRenderHandler::GetShader()->setMat4("model", model);
}

void ChunkRenderer::Draw() {

	//SetUnitNumbers(false);
	if (chunk != nullptr) {

		RenderSetup();

		if (chunk->CheckForRenderUpdate() || chunk != previousChunk) {
			SetUnitInfo(false);
			previousChunk = chunk;
			chunk->Rendered();
		}
		//bind vao
		glBindVertexArray(VAO);
		//render chunk
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, CHUNK_SIZE * CHUNK_SIZE);

		

		
	}
	else {
		std::cout << "ERROR::no chunk set to render" << std::endl;
		return;
	}
	


}

