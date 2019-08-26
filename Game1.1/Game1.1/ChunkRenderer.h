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

	void RenderSetup();

	void SetPositions();
	void SetUnitInfo(bool);
	void SetTextureCoordinates();
	void SetBasicTextureCoordinates();

	unsigned int VAO;
	//0:shape
	//1:position
	//2:unit number
	//3:texCoords
	//4:basicTexCoords
	unsigned int VBO[5];
	unsigned int EBO;

	Chunk* previousChunk = nullptr;

	Chunk* chunk = nullptr;

	glm::ivec2* positions;

	glm::ivec2* unitNumbers;



};

