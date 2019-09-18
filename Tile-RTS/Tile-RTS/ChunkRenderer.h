#pragma once
#include "Shader.h"

class Chunk;

class ChunkRenderer
{
public:
	ChunkRenderer();
	~ChunkRenderer();

	void Draw();

	void SetChunk(Chunk* chunk);
	Chunk* GetChunk();

	void UpdateSingleUnitRender(glm::ivec2 position, glm::ivec2 info);

private:
	void Init();
	void InitUnitInfo();

	void RenderSetup();

	void SetPositions();
	void SetUnitInfo();
	void SetTextureCoordinates();
	void SetBasicTextureCoordinates();

	unsigned int VAO;
	//0:shape
	//1:position
	//2:unit info
	//2:texCoords
	//3:basicTexCoords
	unsigned int VBO[5];
	unsigned int EBO;


	Chunk* previousChunk = nullptr;

	Chunk* chunk = nullptr;

	glm::ivec2* positions;

	glm::ivec2* unitNumbers;

	void* unitBufferPtr = nullptr;

};

